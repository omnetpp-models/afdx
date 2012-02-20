//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#ifndef QUEUEINGUTILS_H_
#define QUEUEINGUTILS_H_

#include "QueueingDefs.h"

namespace queueing {

QUEUEING_API int findField(cObject *obj, const char *fieldName);
QUEUEING_API std::string getFieldByName(cObject *obj, const char *fieldName);
QUEUEING_API long getFieldAsLong(cObject *obj, const char *fieldName);

}
#endif /* QUEUEINGUTILS_H_ */
