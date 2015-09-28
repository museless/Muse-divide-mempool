# MDPool

## Overview
**MDPool**, a memory divide pool


## Brief introduction
A memory pool, when you need to malloc many size fixed
piece, you can use it replace malloc/free new/delete


## Advantage/Disadvantage
**Adv**
1. It's speed as same as malloc, new when malloc small pieces
2. Do not need to manage pieces

**Disadv**
1. May be waste many memory space when you malloc size unstable pieces
2. Bad performace when using it to malloc large piece


## Usage
Easy understanding api for everyone

**First Move**
Calling "mmdp_create()" to get a DMPH stru pointer
Warning: when argument 1 borderSize for mmdp_create smaller than DEFAULT_BSIZE
it will use DEFAULT_BSIZE replace borderSize to be a small chunk size

**Second Move**
1. malloc memory "mmdp_malloc()"
2. "mmdp_free_handler()" just free the DMPH stru
3. "mmdp_free_pool()" free the whole pool(DMPH stru and the memory that pool malloced)
4. "mmdp_free()" just free the memory space that the memory space called by mmdp_malloc
5. "mmdp_reset_default()" to make the small chunk reuseable. But careful, you need to sure no one use that chunk anymore

