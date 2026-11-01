#ifndef EXEC_ERRORS_H
#define EXEC_ERRORS_H
/*
 * OpenNDK: the error codes devices return in io_Error.
 * Copyright (c) 2026 AmiCradle Team. MIT licence (see OpenNDK/LICENSE).
 */

#define IOERR_OPENFAIL	 (-1)	/* the device or unit would not open */
#define IOERR_ABORTED	 (-2)	/* AbortIO() ended the request */
#define IOERR_NOCMD	 (-3)	/* command not supported */
#define IOERR_BADLENGTH	 (-4)	/* length not valid */
#define IOERR_BADADDRESS (-5)	/* address not valid */
#define IOERR_UNITBUSY	 (-6)	/* unit already in use */
#define IOERR_SELFTEST	 (-7)	/* hardware failed its self test */

#endif /* EXEC_ERRORS_H */
