/*

Copyright (C) 2026 BubbleRAN

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#ifndef CHANGE_TYPE_H
#define  CHANGE_TYPE_H

typedef enum {
  CHANGE_TYPE_NONE,
  CHANGE_TYPE_MODIFICATION,
  CHANGE_TYPE_ADDITION,
  CHANGE_TYPE_DELETION,

  END_CHANGE_TYPE
} change_type_e;


#endif
