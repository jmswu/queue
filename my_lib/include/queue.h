/**
 * @file queue.h
 * @author James Wu(jameswu62@yahoo.co.nz)
 * @brief C code example
 * @version 0.1
 * @date 2022-02-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int add_c_code(int a, int b);
int add_with_cb(int a, int b, int (*cb)(int, int));

#ifdef __cplusplus
}
#endif