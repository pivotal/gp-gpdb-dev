/*
 * pxf_option.h
 *		  Foreign-data wrapper option handling for PXF (Platform Extension Framework)
 *
 * IDENTIFICATION
 *		  contrib/pxf_fdw/pxf_option.h
 */

#include "postgres.h"

#include "pxf_curl.h"
#include "nodes/pg_list.h"

#ifndef _PXF_OPTION_H_
#define _PXF_OPTION_H_

/*
 * Structure to store the PXF options
 */
typedef struct PxfOptions
{
	/* PXF service options */
	int			pxf_port;		/* port number for the PXF Service */
	char	   *pxf_host;		/* hostname for the PXF Service */
	char	   *pxf_protocol;	/* protocol for the PXF Service (i.e HTTP or
								 * HTTPS) */

	/* Server doesn't come from options, it is the actual SERVER name */
	char	   *server;			/* the name of the external server */

	/* Defined at options, but it is not visible to FDWs */
	char		exec_location;	/* execute on MASTER, ANY or ALL SEGMENTS,
								 * Greenplum MPP specific */

	/* Single Row Error Handling */
	int			reject_limit;
	bool		is_reject_limit_rows;
	bool		log_errors;

	/* FDW options */
	char	   *protocol;		/* PXF protocol */
	char	   *resource;		/* PXF resource */
	char	   *format;			/* PXF resource format */
	char	   *profile;		/* protocol[:format] */
	char	   *wire_format;		/* The format on the wire */

	List	   *copy_options;	/* merged options for COPY */
	List	   *options;		/* merged options, excluding COPY, protocol,
								 * resource, format, wire_format, pxf_port,
								 * pxf_host, and pxf_protocol */

	/* SSL options */
	PxfSSLOptions	 *ssl_options; /* SSL options for CURL */
} PxfOptions;

/* Functions prototypes for pxf_option.c file */
PxfOptions *PxfGetOptions(Oid foreigntableid);

#endif							/* _PXF_OPTION_H_ */