//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

package afdx;

import afdx.queueinglib.PassiveQueue;
import afdx.queueinglib.Sink;


//
// This module represents an EndSystem device in an AFDX network. It has two 
// separate ethernet interfaces which should be attached to different networks
//
module EndSystem
{
    @display("i=device/device;bgb=489,298");
    gates:
        inout ethPortA @labels(eth100);
        inout ethPortB @labels(eth100);
    submodules:
        trafficSource1: AFDXMessageSource {
            @display("p=59,44");
        }
        trafficSink: Sink {
            @display("p=59,228");
        }
        macB: MAC {
            @display("p=450,189");
        }
        macA: MAC {
            @display("p=450,119");
        }
        txQueueA: PassiveQueue {
            @display("p=356,44");
        }
        txQueueB: PassiveQueue {
            @display("p=356,119");
        }
        integrityCheckerA: IntegrityChecker {
            @display("p=356,189");
        }
        integrityCheckerB: IntegrityChecker {
            @display("p=356,257");
        }
        regulatorLogic: RegulatorLogic {
            @display("p=155,44");
        }
        redundancyChecker: RedundancyChecker {
            @display("p=242,228");
        }
        redundancyController: RedundancyController {
            @display("p=254,83");
        }
    connections:
        ethPortA <--> macA.eth;
        ethPortB <--> macB.eth;
        txQueueA.out++ --> macA.in++;
        txQueueB.out++ --> macB.in++;
        macA.out --> integrityCheckerA.in;
        macB.out --> integrityCheckerB.in;
        integrityCheckerA.out --> redundancyChecker.inA;
        integrityCheckerB.out --> redundancyChecker.inB;
        trafficSource1.out --> regulatorLogic.in;
        redundancyChecker.out --> trafficSink.in++;
        regulatorLogic.out --> redundancyController.in++;
        redundancyController.outA --> txQueueA.in++;
        redundancyController.outB --> txQueueB.in++;
}
