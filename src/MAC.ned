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

//
// Handles the TX/RX over the ethernet cable. 
// Encasulation/decasulation is done here i.e. the packetLength is modified to
// add/substract the ethernet frame size. Also preamble and IFG is handled here  
// TX: Invalid or expired packets are dropped.
// RX: timestamp the message with last bit received time.
//
simple MAC
{
    @display("i=block/rxtx");
    string fetchingAlgorithm @enum("priority","random","roundRobin","longestQueue") = default("roundRobin");
             // how the next job will be choosen from the attached queues
    double maxFrameAge @unit("s") = default(1s);
    gates:
        inout eth;
        input in[];
        output out;
}
