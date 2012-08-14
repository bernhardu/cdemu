/*
 *  libMirage: Debugging facilities
 *  Copyright (C) 2006-2012 Rok Mandeljc
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __MIRAGE_DEBUG_H__
#define __MIRAGE_DEBUG_H__


/* Debug masks */
/**
 * MIRAGE_DebugMasks:
 * @MIRAGE_DEBUG_ERROR: error message
 * @MIRAGE_DEBUG_WARNING: warning message
 * @MIRAGE_DEBUG_PARSER: message belonging to parser
 * @MIRAGE_DEBUG_DISC: message belonging to disc
 * @MIRAGE_DEBUG_SESSION: message belonging to session
 * @MIRAGE_DEBUG_TRACK: message belonging to track
 * @MIRAGE_DEBUG_SECTOR: message belonging to sector
 * @MIRAGE_DEBUG_FRAGMENT: message belonging to fragment
 * @MIRAGE_DEBUG_CDTEXT: message belonging to CD-TEXT encoder/decoder
 * @MIRAGE_DEBUG_FILE: messages belonging to file filter
 *
 * <para>
 * Debug message types and debug masks used to control verbosity of various
 * parts of libMirage.
 * </para>
 *
 * <para>
 * All masks except %MIRAGE_DEBUG_ERROR and %MIRAGE_DEBUG_WARNING can be combined
 * together to control verbosity of libMirage.
 * </para>
 **/
typedef enum
{
    /* Debug types */
    MIRAGE_DEBUG_ERROR    = 0x00F1,
    MIRAGE_DEBUG_WARNING  = 0x00F2,
    /* Debug masks */
    MIRAGE_DEBUG_PARSER   = 0x0001,
    MIRAGE_DEBUG_DISC     = 0x0002,
    MIRAGE_DEBUG_SESSION  = 0x0004,
    MIRAGE_DEBUG_TRACK    = 0x0008,
    MIRAGE_DEBUG_SECTOR   = 0x0010,
    MIRAGE_DEBUG_FRAGMENT = 0x0020,
    MIRAGE_DEBUG_CDTEXT   = 0x0040,
    MIRAGE_DEBUG_FILE   = 0x0080,
} MIRAGE_DebugMasks;


/**
 * MIRAGE_DEBUG:
 * @obj: object
 * @lvl: debug level
 * @msg...: debug message
 *
 * <para>
 * Debugging macro, provided for convenience. It performs cast to #MIRAGE_Debuggable
 * interface on @obj, then calls mirage_debuggable_message() with debug level @lvl and
 * debug message @msg....
 * </para>
 **/
#define MIRAGE_DEBUG(obj, lvl, msg...) { \
    mirage_debuggable_debug_message(MIRAGE_DEBUGGABLE(obj), lvl, msg); \
}


G_BEGIN_DECLS


/**********************************************************************\
 *                        Debuggable interface                        *
\**********************************************************************/
#define MIRAGE_TYPE_DEBUGGABLE                 (mirage_debuggable_get_type())
#define MIRAGE_DEBUGGABLE(obj)                 (G_TYPE_CHECK_INSTANCE_CAST((obj), MIRAGE_TYPE_DEBUGGABLE, MIRAGE_Debuggable))
#define MIRAGE_IS_DEBUGGABLE(obj)              (G_TYPE_CHECK_INSTANCE_TYPE((obj), MIRAGE_TYPE_DEBUGGABLE))
#define MIRAGE_DEBUGGABLE_GET_INTERFACE(inst)  (G_TYPE_INSTANCE_GET_INTERFACE((inst), MIRAGE_TYPE_DEBUGGABLE, MIRAGE_DebuggableInterface))

/**
 * MIRAGE_Debuggable:
 *
 * <para>
 * Dummy interface structure.
 * </para>
 **/
typedef struct _MIRAGE_Debuggable             MIRAGE_Debuggable;
typedef struct _MIRAGE_DebuggableInterface    MIRAGE_DebuggableInterface;

struct _MIRAGE_DebuggableInterface
{
    GTypeInterface parent_iface;

    /* Interface methods */
    void (*set_debug_context) (MIRAGE_Debuggable *self, GObject *debug_context);
    GObject *(*get_debug_context) (MIRAGE_Debuggable *self);

    void (*debug_message) (MIRAGE_Debuggable *self, gint level, gchar *format, ...);
    void (*debug_messagev) (MIRAGE_Debuggable *self, gint level, gchar *format, va_list args);
};

/* Used by MIRAGE_TYPE_DEBUGGABLE */
GType mirage_debuggable_get_type (void);

/* Public API */
void mirage_debuggable_set_debug_context (MIRAGE_Debuggable *self, GObject *debug_context);
GObject *mirage_debuggable_get_debug_context (MIRAGE_Debuggable *self);

void mirage_debuggable_debug_message (MIRAGE_Debuggable *self, gint level, gchar *format, ...);
void mirage_debuggable_debug_messagev (MIRAGE_Debuggable *self, gint level, gchar *format, va_list args);


/**********************************************************************\
 *                        Debug context object                        *
\**********************************************************************/
#define MIRAGE_TYPE_DEBUG_CONTEXT            (mirage_debug_context_get_type())
#define MIRAGE_DEBUG_CONTEXT(obj)            (G_TYPE_CHECK_INSTANCE_CAST((obj), MIRAGE_TYPE_DEBUG_CONTEXT, MIRAGE_DebugContext))
#define MIRAGE_DEBUG_CONTEXT_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST((klass), MIRAGE_TYPE_DEBUG_CONTEXT, MIRAGE_DebugContextClass))
#define MIRAGE_IS_DEBUG_CONTEXT(obj)         (G_TYPE_CHECK_INSTANCE_TYPE((obj), MIRAGE_TYPE_DEBUG_CONTEXT))
#define MIRAGE_IS_DEBUG_CONTEXT_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), MIRAGE_TYPE_DEBUG_CONTEXT))
#define MIRAGE_DEBUG_CONTEXT_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS((obj), MIRAGE_TYPE_DEBUG_CONTEXT, MIRAGE_DebugContextClass))

typedef struct _MIRAGE_DebugContext         MIRAGE_DebugContext;
typedef struct _MIRAGE_DebugContextClass    MIRAGE_DebugContextClass;
typedef struct _MIRAGE_DebugContextPrivate  MIRAGE_DebugContextPrivate;

/**
 * MIRAGE_DebugContext:
 *
 * <para>
 * Contains private data only, and should be accessed using the functions below.
 * </para>
 **/
struct _MIRAGE_DebugContext
{
    GObject parent_instance;

    /*< private >*/
    MIRAGE_DebugContextPrivate *priv;
};

struct _MIRAGE_DebugContextClass
{
    GObjectClass parent_class;
};

/* Used by MIRAGE_TYPE_DEBUG_CONTEXT */
GType mirage_debug_context_get_type (void);

/* Public API */
void mirage_debug_context_set_debug_mask (MIRAGE_DebugContext *self, gint debug_mask);
gint mirage_debug_context_get_debug_mask (MIRAGE_DebugContext *self);

void mirage_debug_context_set_domain (MIRAGE_DebugContext *self, const gchar *domain);
const gchar *mirage_debug_context_get_domain (MIRAGE_DebugContext *self);

void mirage_debug_context_set_name (MIRAGE_DebugContext *self, const gchar *name);
const gchar *mirage_debug_context_get_name (MIRAGE_DebugContext *self);


G_END_DECLS

#endif /* __MIRAGE_DEBUG_H__ */
