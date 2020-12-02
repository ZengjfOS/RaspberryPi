#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include <linux/types.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "binder.h"

#define SVR_CMD_ADD_ONE         0
#define SVR_CMD_REDUCE_ONE      1

int addone(int n);
int reduceone(int n);
uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name);

struct binder_state *g_bs;
uint32_t g_handle;

#include <sys/time.h>

long long current_timestamp() {
    struct timeval te; 
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds

    printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

int main(int argc, char **argv)
{
	struct binder_state *bs;
	uint32_t svcmgr = BINDER_SERVICE_MANAGER;
	uint32_t handle;
	int ret;
	/* 一样的，先打开 Binder 驱动 */
	bs = binder_open("/dev/binder", 128*1024);
	if (!bs) {
		fprintf(stderr, "failed to open binder driver\n");
		return -1;
	}
	g_bs = bs;
	/* 查询服务，获得服务 handle */
	handle = svcmgr_lookup(bs, svcmgr, "calculate");
	if (!handle) {
		fprintf(stderr, "failed to get addone service\n");
		return -1;
	}
	g_handle = handle;
	/* send data to server */
	if (!strcmp(argv[1], "a")) {
		current_timestamp();
		// usleep(1000 * 1000);
		ret = addone(atoi(argv[2]));
		current_timestamp();
		fprintf(stderr, "get ret of addone= %d\n", ret);
	} else if (!strcmp(argv[1], "r")) {
		ret = reduceone(atoi(argv[2]));
		fprintf(stderr, "get ret of reduceone= %d\n", ret);
	}
	/* Client 使用完就释放服务 */
	binder_release(bs, handle);
	return 0;
}

uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *name)
{
	uint32_t handle;
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	/* 构造 binder_io 参数是想要获取 service 的名字 */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header
	bio_put_string16_x(&msg, SVC_MGR_NAME);
	bio_put_string16_x(&msg, name);

	/* 查询服务是否存在 */
	if (binder_call(bs, &msg, &reply, target, SVC_MGR_CHECK_SERVICE))
		return 0;

	/* 得到服务的 handle */
	handle = bio_get_ref(&reply);

	/* 申请服务，用完 release */
	if (handle)
		binder_acquire(bs, handle);
	binder_done(bs, &msg, &reply);
	return handle;
}

int addone(int n)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;
	/* 构造binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header
	/* 放入参数 */
	bio_put_uint32(&msg, n); 
	/* 调用binder_call */
	if (binder_call(g_bs, &msg, &reply, g_handle, SVR_CMD_ADD_ONE))
		return 0;
	/* 从reply中解析出返回值 */
	ret = bio_get_uint32(&reply);
	binder_done(g_bs, &msg, &reply);
	return ret;
}

int reduceone(int n)
{
	unsigned iodata[512/4];
	struct binder_io msg, reply;
	int ret;
	/* 构造binder_io */
	bio_init(&msg, iodata, sizeof(iodata), 4);
	bio_put_uint32(&msg, 0);  // strict mode header
	/* 放入参数 */
	bio_put_uint32(&msg, n);
	/* 调用binder_call */
	if (binder_call(g_bs, &msg, &reply, g_handle, SVR_CMD_REDUCE_ONE))
		return 0;
	/* 从reply中解析出返回值 */
	ret = bio_get_uint32(&reply);
	binder_done(g_bs, &msg, &reply);
	return ret;
}
