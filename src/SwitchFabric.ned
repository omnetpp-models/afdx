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

import afdx.queueinglib.Classifier;
import afdx.queueinglib.PassiveQueue;
import afdx.queueinglib.Server;


//
// Handles the routing frames on different virtual links.
// If an output port cannot handle the output packet (busy, down)
// the packet should be dropped. If a packed is too old 
// (calculated transmission time of last bit - reception time of last bit) 
// it should be dropped too. maxPacketAge is specified for each port.
//
module SwitchFabric
{
    @display("i=block/fork;bgb=427,186");
    gates:
        inout port[];
    submodules:
        priorityClassifier: Classifier {
            @display("p=60,82");
            dispatchField = "priority";
            gates:
                out[2];
        }
        lowQueue: PassiveQueue {
            @display("p=149,133");
        }
        highQueue: PassiveQueue {
            @display("p=149,37");
        }
        scheduler: Server {
            @display("p=245,82");
            gates:
                in[2];
        }
        router: VLRouter {
            @display("p=338,82");
            gates:
                out[sizeof(port)];
        }
    connections:
        for i=0..sizeof(port)-1 {
            port$i[i] --> priorityClassifier.in++;
        }

        priorityClassifier.out[0] --> highQueue.in++;
        priorityClassifier.out[1] --> lowQueue.in++;
        highQueue.out++ --> scheduler.in[0];
        lowQueue.out++ --> scheduler.in[1];
        scheduler.out --> router.in++;

        for i=0..sizeof(port)-1 {
            router.out[i] --> port$o[i];
        }
}
