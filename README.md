# README

这个版本是自己根据Android源代码servicemanger进行移植的

## 参考文档

* https://github.com/ZengjfOS/RaspberryPi/tree/binder4linux

## servicemanager test steps

* sudo ./bctest publish zengjf

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./bctest publish zengjf
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 06 . 00 . 00 . 00 . 7a z 00 . 65 e 00 . 6e n 00 . 67 g 00 . 6a j 00 . 66 f 00 .
  0080: 00 . 00 . fd . b6 . 85 . 2a * 62 b 73 s 7f . 01 . 00 . 00 . 70 p 30 0 02 . 00 .
  0096: 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
  BR_NOOP:
  BR_INCREFS:
    0xbea5c2fc, 0xbea5c300
  BR_ACQUIRE:
    0xbea5c310, 0xbea5c314
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 4  offs 0
  0000: 00 . 00 . 00 . 00 .
  ```

* sudo ./bctest lookup zengjf

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./bctest lookup zengjf
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 06 . 00 . 00 . 00 . 7a z 00 . 65 e 00 . 6e n 00 . 67 g 00 . 6a j 00 . 66 f 00 .
  0080: 00 . 00 . f9 . b6 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 24  offs 8
  0000: 85 . 2a * 68 h 73 s 7f . 01 . 00 . 00 . 01 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
  0016: 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
    - type 73682a85  flags 0000017f  ptr 0000000000000001  cookie 0000000000000000
  lookup(zengjf) = 1
  ```

* sudo ./servicemanager

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./servicemanager
  BR_NOOP:
  BR_TRANSACTION:
    target 0000000000000000  cookie 0000000000000000  code 00000003  flags 00000000
    pid     4469  uid        0  data 108  offs 8
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 06 . 00 . 00 . 00 . 7a z 00 . 65 e 00 . 6e n 00 . 67 g 00 . 6a j 00 . 66 f 00 .
  0080: 00 . 00 . fd . b6 . 85 . 2a * 68 h 73 s 7f . 01 . 00 . 00 . 01 . 00 . 00 . 00 .
  0096: 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
    - type 73682a85  flags 0000017f  ptr 0000000000000001  cookie 0000000000000000
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_NOOP:
  BR_TRANSACTION:
    target 0000000000000000  cookie 0000000000000000  code 00000002  flags 00000000
    pid     4477  uid        0  data 84  offs 0
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 06 . 00 . 00 . 00 . 7a z 00 . 65 e 00 . 6e n 00 . 67 g 00 . 6a j 00 . 66 f 00 .
  0080: 00 . 00 . f9 . b6 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  ```

* sudo ./bctest alt

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./bctest alt
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 0b . 00 . 00 . 00 . 61 a 00 . 6c l 00 . 74 t 00 . 5f _ 00 . 73 s 00 . 76 v 00 .
  0080: 63 c 00 . 5f _ 00 . 6d m 00 . 67 g 00 . 72 r 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 4  offs 0
  0000: 00 . 00 . 00 . 00 .
  cannot find alt_svc_mgr
  ```

  * 这里失败的原因主要是因为没注册这个service，所以需要先publish alt_svc_mgr这个service还行；
  * sudo ./bctest publish alt_svc_mgr

## service client test steps

* sudo ./servicemanager

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./servicemanager
  BR_NOOP:
  BR_TRANSACTION:
    target 0000000000000000  cookie 0000000000000000  code 00000002  flags 00000000
    pid     4743  uid        0  data 88  offs 0
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 09 . 00 . 00 . 00 . 63 c 00 . 61 a 00 . 6c l 00 . 63 c 00 . 75 u 00 . 6c l 00 .
  0080: 61 a 00 . 74 t 00 . 65 e 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_NOOP:
  BR_TRANSACTION:
    target 0000000000000000  cookie 0000000000000000  code 00000002  flags 00000000
    pid     4884  uid        0  data 88  offs 0
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 09 . 00 . 00 . 00 . 63 c 00 . 61 a 00 . 6c l 00 . 63 c 00 . 75 u 00 . 6c l 00 .
  0080: 61 a 00 . 74 t 00 . 65 e 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  ```
* sudo ./service

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./service
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 09 . 00 . 00 . 00 . 63 c 00 . 61 a 00 . 6c l 00 . 63 c 00 . 75 u 00 . 6c l 00 .
  0080: 61 a 00 . 74 t 00 . 65 e 00 . 00 . 00 . 85 . 2a * 62 b 73 s 7f . 01 . 00 . 00 .
  0096: 7b { 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
  BR_NOOP:
  BR_INCREFS:
    0xbea1b31c, 0xbea1b320
  BR_ACQUIRE:
    0xbea1b330, 0xbea1b334
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 4  offs 0
  0000: 00 . 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION:
    target 000000000000007b  cookie 0000000000000000  code 00000000  flags 00000000
    pid     4884  uid        0  data 8  offs 0
  0000: 00 . 00 . 00 . 00 . 79 y 00 . 00 . 00 .
  i am server,add one 121
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  ```

* sudo ./client a 121

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./client a 121
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 09 . 00 . 00 . 00 . 63 c 00 . 61 a 00 . 6c l 00 . 63 c 00 . 75 u 00 . 6c l 00 .
  0080: 61 a 00 . 74 t 00 . 65 e 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 24  offs 8
  0000: 85 . 2a * 68 h 73 s 7f . 01 . 00 . 00 . 01 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
  0016: 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
    - type 73682a85  flags 0000017f  ptr 0000000000000001  cookie 0000000000000000
  0000: 00 . 00 . 00 . 00 . 79 y 00 . 00 . 00 .
  BR_NOOP:
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 4  offs 0
  0000: 7a z 00 . 00 . 00 .
  get ret of addone= 122
  ```

## Publish数据格式

* sudo ./bctest publish zengjf

  ```bash
  pi@raspberrypi:~/zengjf/servicemanager $ sudo ./bctest publish zengjf
  0000: 00 . 00 . 00 . 00 . 1a . 00 . 00 . 00 . 61 a 00 . 6e n 00 . 64 d 00 . 72 r 00 .
  0016: 6f o 00 . 69 i 00 . 64 d 00 . 2e . 00 . 6f o 00 . 73 s 00 . 2e . 00 . 49 I 00 .
  0032: 53 S 00 . 65 e 00 . 72 r 00 . 76 v 00 . 69 i 00 . 63 c 00 . 65 e 00 . 4d M 00 .
  0048: 61 a 00 . 6e n 00 . 61 a 00 . 67 g 00 . 65 e 00 . 72 r 00 . 00 . 00 . 00 . 00 .
  0064: 06 . 00 . 00 . 00 . 7a z 00 . 65 e 00 . 6e n 00 . 67 g 00 . 6a j 00 . 66 f 00 .
  0080: 00 . 00 . fd . b6 . 85 . 2a * 62 b 73 s 7f . 01 . 00 . 00 . 70 p 30 0 02 . 00 .
  0096: 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 . 00 .
  BR_NOOP:
  BR_INCREFS:
    0xbea5c2fc, 0xbea5c300
  BR_ACQUIRE:
    0xbea5c310, 0xbea5c314
  BR_TRANSACTION_COMPLETE:
  BR_REPLY:
    target 0000000000000000  cookie 0000000000000000  code 00000000  flags 00000000
    pid        0  uid        0  data 4  offs 0
  0000: 00 . 00 . 00 . 00 .
  ```
* publish code

  ```C
  int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, void *ptr)
  {
      int status;
      // 128 bytes
      unsigned iodata[512/4];
      struct binder_io msg, reply;
  
      bio_init(&msg, iodata, sizeof(iodata), 4);
      // 4 bytes with 0
      bio_put_uint32(&msg, 0);  // strict mode header
      /**
       * * start with 4 bytes with len and following with string and '\0' for end string：
       *   bio_put_uint32(bio, len);
       *   ptr = bio_alloc(bio, (len + 1) * sizeof(uint16_t));
       * * bio_alloc采用了4字节对齐，所以你会看到这一段多出了2个byte，(54 + 2) % 4 = 0；
       *   size = (size + 3) & (~3);
       */
      bio_put_string16_x(&msg, SVC_MGR_NAME);
      // start with 4 bytes with len and following with string and '\0' for end string：
      bio_put_string16_x(&msg, name);
      bio_put_obj(&msg, ptr);
  
      if (binder_call(bs, &msg, &reply, target, SVC_MGR_ADD_SERVICE))
          return -1;
  
      status = bio_get_uint32(&reply);
  
      binder_done(bs, &msg, &reply);
  
      return status;
  }
  ```

## Android版本导致的bctest无法使用补丁

* https://android.googlesource.com/platform/frameworks/native/+/refs/heads/android10-mainline-release/cmds/servicemanager/service_manager.c#283
  ```
  // Equivalent to Parcel::enforceInterface(), reading the RPC
  // header with the strict mode policy mask and the interface name.
  // Note that we ignore the strict_policy and don't propagate it
  // further (since we do no outbound RPCs anyway).
  strict_policy = bio_get_uint32(msg);
  bio_get_uint32(msg);  // Ignore worksource header.      <--------------------
  s = bio_get_string16(msg, &len);
  if (s == NULL) {
      return -1;
  }
  ```
* 通信协议里面多加了一个uint32，导致servicemanager数据获取处理出错：
  ```diff
  diff --git a/frameworks/native/cmds/servicemanager/bctest.c b/frameworks/native/cmds/servicemanager/bctest.c
  index 354df670e54..782bf29e958 100644
  --- a/frameworks/native/cmds/servicemanager/bctest.c
  +++ b/frameworks/native/cmds/servicemanager/bctest.c
  @@ -16,6 +16,7 @@ uint32_t svcmgr_lookup(struct binder_state *bs, uint32_t target, const char *nam

       bio_init(&msg, iodata, sizeof(iodata), 4);
       bio_put_uint32(&msg, 0);  // strict mode header
  +    bio_put_uint32(&msg, 0);
       bio_put_string16_x(&msg, SVC_MGR_NAME);
       bio_put_string16_x(&msg, name);

  @@ -40,6 +41,7 @@ int svcmgr_publish(struct binder_state *bs, uint32_t target, const char *name, v

       bio_init(&msg, iodata, sizeof(iodata), 4);
       bio_put_uint32(&msg, 0);  // strict mode header
  +    bio_put_uint32(&msg, 0);
       bio_put_string16_x(&msg, SVC_MGR_NAME);
       bio_put_string16_x(&msg, name);
       bio_put_obj(&msg, ptr);
  @@ -93,9 +95,12 @@ int main(int argc, char **argv)
                   fprintf(stderr,"argument required\n");
                   return -1;
               }
  +            fprintf(stderr,"published: [%s]\n", argv[1]);
               svcmgr_publish(bs, svcmgr, argv[1], &token);
               argc--;
               argv++;
  +
  +            while(1);
           } else {
               fprintf(stderr,"unknown command %s\n", argv[0]);
               return -1;
  ```

