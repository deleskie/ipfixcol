/**
 * \file Cursor.h
 * \author Petr Velan <petr.velan@cesnet.cz>
 * \brief Header of class wrapping ibis::table::cursor
 *
 * Copyright (C) 2011 CESNET, z.s.p.o.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name of the Company nor the names of its contributors
 *    may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * ALTERNATIVELY, provided that this notice is retained in full, this
 * product may be distributed under the terms of the GNU General Public
 * License (GPL) version 2 or later, in which case the provisions
 * of the GPL apply INSTEAD OF those given above.
 *
 * This software is provided ``as is, and any express or implied
 * warranties, including, but not limited to, the implied warranties of
 * merchantability and fitness for a particular purpose are disclaimed.
 * In no event shall the company or contributors be liable for any
 * direct, indirect, incidental, special, exemplary, or consequential
 * damages (including, but not limited to, procurement of substitute
 * goods or services; loss of use, data, or profits; or business
 * interruption) however caused and on any theory of liability, whether
 * in contract, strict liability, or tort (including negligence or
 * otherwise) arising in any way out of the use of this software, even
 * if advised of the possibility of such damage.
 *
 */

#ifndef CURSOR_H_
#define CURSOR_H_

#include <ibis.h>
#include <string>
#include "AST.h"
#include "Table.h"

namespace ipfixdump {

/* Table and Cursor classes are dependent on each other */
class Table;

/**
 * \brief Class Cursor wrapping ibis::table::cursor
 *
 * This class should also implement filtering on composed columns
 */
class Cursor
{
public:
	/**
	 * \brief Cursor class constructor
	 *
	 * @param table which cursor should be wrapped
	 */
	Cursor(Table &table);

	/**
	 * \brief Fetch next line. Must be called before trying to access row data
	 * This function should implement some kind of filter on composed columns
	 * and skip non-matching rows TODO
	 *
	 * @return true on success, false otherwise
	 */
	bool next();

	/**
	 * \brief Get column value and return it as a string
	 *
	 * @param[in] name Name of the fastbit column to get value for
	 * @param[out] value Values structure with column values
	 * @param[in] part Number of part to write result to
	 * @return true on success, false otherwise
	 */
	bool getColumn(const char *name, values &value, int part);

	/**
	 * \brief Cursor class destructor
	 */
	~Cursor();

private:
	Table &table; /**< Table of the cursor */
	ibis::table::cursor *cursor; /**< Ibis cursor to wrap */
};

} /* end of namespace ipfixdump */


#endif /* CURSOR_H_ */
