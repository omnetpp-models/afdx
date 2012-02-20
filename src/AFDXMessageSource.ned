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

import afdx.queueinglib.Source;


//
// TODO auto-generated module
//
simple AFDXMessageSource extends Source
{
    @class(AFDXMessageSource);
    volatile int packetLength = default(128);       // the legth of AFDX Ethernet frame
    volatile int networkId;       // (1) used as [n]
    volatile int equipmentId;     // (1) used as [e]
    volatile int interfaceId;     // (3bit) used as [i] 
    volatile int virtualLinkId;   // (2) used as [v]
    volatile int seqNum;          // (1) used as [s]
    volatile int partitionId;     // (5bit) used as [p] 
    volatile int udpSrcPort;    // (2)
    volatile int udpDestPort;   // (2)
}
