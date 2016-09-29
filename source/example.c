/*---------------------------------------------
 *     modification time: 2016-07-12 18:29:21
 *     mender: Muse
-*---------------------------------------------*/

/*---------------------------------------------
 *     file: example.c
 *     creation time: 2016-07-12 18:29:21
 *     author: Muse
-*---------------------------------------------*/

#include "mempool.h"
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


#define TIME_DIFF(s, e) \
    ((e.tv_sec * 1000000 + e.tv_usec) - (s.tv_sec * 1000000 + s.tv_usec))


int main(void)
{
    Mempool  pool;

    if (!mmdp_create(&pool, 0x8000)) {
        perror("mmdp_create");
        return  -1;
    }

    void __attribute__ ((unused))  *ptr;
    bool __attribute__ ((unused))   need_free = false;

    struct timeval  end, start;
    unsigned long   tma = 0, tmm = 0;
    int32_t         size = 0;

    srandom(time(NULL));

    for (int idx = 0; idx < 1000000; idx++) {
        size = random() % 2048 + 1;
        //printf("Size: %d\n", size);
        if (size > 1024)
            need_free = true;

        gettimeofday(&start, NULL);

        if (!(ptr = malloc(size)))
            perror("malloc");

        if (need_free)
            free(ptr);

        gettimeofday(&end, NULL);

        tma += TIME_DIFF(start, end); 

        gettimeofday(&start, NULL);
        ptr = mmdp_malloc(&pool, size);

        if (need_free)
            mmdp_free(&pool, ptr);

        gettimeofday(&end, NULL);

        tmm += TIME_DIFF(start, end);
        need_free = false;
    }

    printf("Chunk: %d\n", pool.nchunk);
    printf("Malloc: %ld us - Musepool: %ld us\n", tma, tmm);

    mmdp_free_pool(&pool);

    return  -1;
}

