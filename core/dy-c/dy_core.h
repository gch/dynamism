#ifndef __DY_CORE_H__
#define __DY_CORE_H__

/* @DYMACRO_DYNAMISM_HEADER_C */

/* Author: Galen Clark Haynes <gchaynes@seas.upenn.edu>
 *
 * dy_core.h: This file defines core methods to initialize the dynamism system,
 * as well as methods to run dynamism processes.
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>
#include <stdio.h>

#define DY_VERSION_MAJOR 0
#define DY_VERSION_MINOR 4
#define DY_VERSION_POINT 2

#define DY_PYTHON 1

#if 1
/* On standard processors, times are represented using floats */
typedef float DyTime;
#else
/* On microprocessors, times are represented using timeval struct */
typedef struct timeval DyTime;
#endif

/* Defined runmodes that reflect state of the system */
typedef enum {
  DY_INIT = 0xA0,
  DY_STARTING = 0xA1,
  DY_RUNNING = 0xA2,
  DY_STOPPING = 0xA3,
  DY_STOPPED = 0xA4,
} DyRunMode;

/* Defined environments from which dynamism is loaded */
typedef enum {
  DY_C_MASTER = 0x50,
  DY_PYTHON_MASTER = 0x51,
  DY_PYTHON_INTERACTIVE_MASTER = 0x52,
  DY_MATLAB_MASTER = 0x53,
} DyMasterType;

/* Initialize dynamism.  This function also initializes all of dynamism's subcomponents. */
void dy_init(int argc, char **argv);

/* Shutdown the system.  This function also shuts down all of dynamism's subcomponents. */
void dy_uninit(void);

/* Start the system, go into infinite loop running update functions. */
void dy_run(void);

/* Start the system manuall, but do not go into infinite loop. */
void dy_start(void);

/* Run a single iteration of the update loop. */
void dy_run_iteration(void);

/* Stop an actively running update loop.  Causes dy_run() to return. */
void dy_stop(void);

/* Exit dynamism. */
void dy_exit(int);

/* Dynamically link and load external library at runtime */
void dy_load_library(const char *);

#if DY_PYTHON
/* Run a python script */
void dy_python_run(const char *);
#endif

/* Retrieve current dynamism system time */
DyTime dy_time(void);

/* Retrieve the current timestep length, as computed in last update loop */
DyTime dy_timestep();

/* Set the desired timestep */
void dy_set_timestep(DyTime);

/* Basic print function */
int dy_printf(const char *, ...);

/* Display a message, identical to printf */
int dy_message(const char *, ...);

/* Display a warning */
int dy_warning(const char *, ...);

/* Display an error and exit */
int dy_error(const char *, ...);

/* Set a debug level.  These are defined as:
 *   0: no debug messages
 *   1: user-level information
 *   2: basic status from routines
 *   3: diagnostic information in routines
 *   4: low-level debug info in routines
*    5: the really nitty-gritty, etc.
 * Return value is previous debug level */
int dy_debug_level(int);
 
/* Display debug messages based upon debug level. */
int dy_debug(int, const char *, ...);

/* Override the default exit function with an alternative exit function */
void dy_set_exit_function(void (*)(int));

/* Override the default print function, rather than printf */
void dy_set_print_function(int (*)(const char*, ...));

/* Set the current master type */
void dy_set_master_type(DyMasterType);

#ifdef __cplusplus
}
#endif

#endif
