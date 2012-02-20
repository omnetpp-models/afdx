//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2006-2008 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

package afdx.queueinglib;

//
// Sends the messages to different outputs depending on a numeric message field.
// If no output gate is found for a message, it is sent to the "rest" gate.
// Messages with field value "i" will be sent to out[i].
//
// @author rhornig
//
simple Classifier
{
    parameters:
        @group(Queueing);
        @display("i=block/classifier");
        string dispatchField = default("kind");
    gates:
        input in[];
        output out[];
        output rest @loose;     // messages that were not classified
}
