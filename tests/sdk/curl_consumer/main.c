/* Copyright (c) 2026 AmiCradle Team. MIT licence. */
#include <errno.h>
#include <curl/curl.h>
#include <proto/exec.h>
#include <proto/bsdsocket.h>
#include <amitcp/socketbasetags.h>

/* OpenAmigaCurl uses the caller task's socket base. The application owns
 * this symbol and opens/configures it before curl, as OpenBrowser does.
 * A multithreaded consumer must audit task/base ownership separately. */
struct Library *SocketBase;
unsigned long __stack = 65536;

int main(void)
{
    CURL *handle = 0;
    int result = 1;
    SocketBase = OpenLibrary((CONST_STRPTR)"bsdsocket.library", 4);
    if (!SocketBase) return 3;
    if (SocketBaseTags(SBTM_SETVAL(SBTC_ERRNOPTR(sizeof(errno))),
                       (ULONG)&errno, TAG_DONE) != 0) goto done;
    if (curl_global_init(CURL_GLOBAL_DEFAULT) != CURLE_OK) goto done;
    handle = curl_easy_init();
    if (handle) curl_easy_cleanup(handle);
    curl_global_cleanup();
    result = handle ? 0 : 2;
done:
    CloseLibrary(SocketBase);
    SocketBase = 0;
    return result;
}
