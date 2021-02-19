#ifndef _TEST_SERVER_H
#define _TEST_SERVER_H
#define SVR_CMD_ADD_ONE         0
#define SVR_CMD_REDUCE_ONE      1
#endif // _TEST_SERVER_H
/* Copyright 2008 The Android Open Source Project
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <stdbool.h>
#include <string.h>
#include "binder.h"

#include <unistd.h>
#include <pthread.h>

#define LOG_TAG "TimeDelayTestService"
#include <cutils/log.h>

pthread_mutex_t mutex;


uint32_t addone(uint32_t n);
uint32_t reduceone(uint32_t n);
int service_handler(struct binder_state *bs, struct binder_transaction_data_secctx *secctx, struct binder_io *msg, struct binder_io *reply);
int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr);

int main(int argc, char **argv)
{
	struct binder_state *bs;
	uint32_t svcmgr = BINDER_SERVICE_MANAGER;
	uint32_t handle;
	int ret;
	
	pthread_mutex_init(&mutex, NULL);

	/* 打开 binder 驱动 */
	bs = binder_open("/dev/binder", 128*1024);
	if (!bs) {
		fprintf(stderr, "failed to open binder driver\n");
		return -1;
	}
	/* 注册服务，最后一个参数不知道干啥用，先随便写 */
	ret = svcmgr_publish(bs, svcmgr, "calculate", (void *)123);
	if (ret) {
		fprintf(stderr, "failed to publish calculate service\n");
		return -1;
	}
	/* 陷入循环，等待 Client 上钩 */
	binder_loop(bs, service_handler);
	return 0;
}

int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr)
{
	int status;
	unsigned iodata[512/4];
	struct binder_io msg, reply;

	/* 构造 binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header
	bio_put_uint32(&msg, 0);
	bio_put_string16_x(&msg, SVC_MGR_NAME);
	bio_put_string16_x(&msg, name);

	/* 暂时不知道干啥用的 */
	bio_put_obj(&msg, ptr);
	if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
		return -1;
	status = bio_get_uint32(&reply);

	/* 这个也不太清楚 */
	binder_done(bs, &msg, &reply);
	return status;
}

int service_handler(struct binder_state *bs,
		struct binder_transaction_data_secctx *secctx,
		struct binder_io *msg,
		struct binder_io *reply)
{
	/* 根据txn->code知道要调用哪一个函数
	 * 如果需要参数, 可以从msg取出
	 * 如果要返回结果, 可以把结果放入reply
	 */
	uint32_t n,result;
	char name[512];
	size_t len;
	uint32_t handle;
	uint32_t strict_policy;
    struct binder_transaction_data *txn = &(secctx->transaction_data);
	// Binder 通信的时候都会先塞个0进去，取数据的一方要先把这个0取出来
	strict_policy = bio_get_uint32(msg);
	switch(txn->code) {
		case SVR_CMD_ADD_ONE:
			/* 从msg里取出要处理的数据,并调用处理函数处理 */
			n = bio_get_uint32(msg);
			pthread_mutex_lock(&mutex);
			ALOGE("start add one\n");
			result = addone(n);
			usleep(1000 * 30);
			/* 把结果放入reply */
			bio_put_uint32(reply, result);
			ALOGE("end add one\n");
			pthread_mutex_unlock(&mutex);
			return 0;
		case SVR_CMD_REDUCE_ONE:
			/* 从msg里取出要处理的数据,并调用处理函数处理 */
			n = bio_get_uint32(msg);
			result = reduceone(n);
			/* 把结果放入reply */
			bio_put_uint32(reply, result);
			return 0;
		default:
			fprintf(stderr, "unknown code %d\n", txn->code);
			return -1;
	}
	return 0;
}

uint32_t addone(uint32_t n)
{
	fprintf(stderr, "i am server,add one %d\n", n);
	return ++n;
}
uint32_t reduceone(uint32_t n)
{
	fprintf(stderr, "i am server,reduce one %d\n", n);
	return --n;
}
