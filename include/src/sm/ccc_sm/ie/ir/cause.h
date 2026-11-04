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

#ifndef CCC_CAUSE_H
#define CCC_CAUSE_H

typedef enum{
  CAUSE_NOT_SUPPORTED,
  CAUSE_NOT_AVAILABLE,
  CAUSE_INCOMPATIBLE_STATE,
  CAUSE_JSON_ERROR,
  CAUSE_SEMANTIC_ERROR,
  CAUSE_UNSPECIFIED,

  END_CAUSE,
} ccc_cause_e;

#endif
