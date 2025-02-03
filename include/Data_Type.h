#ifndef _DATA_TYPE_INTERFACE_H
#define _DATA_TYPE_INTERFACE_H

/* ================================================================ */

/**
 * The function creates a new instance of the given data type.
 */
void* Data_new(const void* dt, ...);

/* ================================ */

/**
 * The function destroys the instance of the given data type and reclaims the associated memory resources.
 */
void Data_delete(void* dt);

/* ================================ */

/**
 * The function outputs the given data type.
 */
void Data_print(const void* dt);

/* ================================================================ */

#endif /* _DATA_TYPE_INTERFACE_H */
