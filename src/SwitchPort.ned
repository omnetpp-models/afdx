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


//
// A port in the switch. 
// During receive handles integrity checking traffic policing and timestamps 
// the message at the arrival of the last bit.
// on sending handles the sendout at physical layer (deals with preamble and IFG too) 
//
module SwitchPort
{
    @display("i=block/ifcard;bgb=315,242");
    double maxPacketAge @unit(s) = default(50ms);
    gates:
        inout ethPort;
        inout toFabric;
    submodules:
        frameFilter: FrameFilter {
            @display("p=159,79");
        }
        trafficPolicy: TrafficPolicy {
            @display("p=253,79");
        }
        mac: MAC {
            @display("p=52,79");
        }
        txQueue: PassiveQueue {
            @display("p=253,169");
        }
    connections:
        ethPort <--> mac.eth;
        mac.out --> frameFilter.in;
        frameFilter.out --> trafficPolicy.in;
        trafficPolicy.out --> toFabric$o;
        txQueue.out++ --> mac.in++;
        toFabric$i --> txQueue.in++;
}
