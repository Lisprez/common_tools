#include <stdio.h>
#include <stdlib.h>
#include <uv.h>
/**
 * libuv.lib
 * ws2_32.lib
 * Psapi.lib
 * Iphlpapi.lib
 * userenv.lib
 * msvcrt.lib
 * 上面这些静态库一定要链接到工程中, 不然就无法使用libuv的静态库
*/

int main() {
	uv_loop_t *loop = (uv_loop_t*)malloc(sizeof(uv_loop_t));
	uv_loop_init(loop);

	printf("Now quitting.\n");
	uv_run(loop, UV_RUN_DEFAULT);

	uv_loop_close(loop);
	free(loop);
	return 0;
}