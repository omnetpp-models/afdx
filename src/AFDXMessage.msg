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

cplusplus {{
#include "queueinglib/Job.h"
}}

message queueing::Job;

namespace afdx;

//
// A Message describing an AFDX msg. (length)  
//
message AFDXMessage extends queueing::Job {
    int networkId;       // (1) used as [n]
    int equipmentId;     // (1) used as [e]
    int interfaceId;     // (3bit) used as [i] 
    int virtualLinkId;   // (2) used as [v]
    int seqNum;          // (1) used as [s]
    int partitionId;     // (5bit) used as [p] 

    // preamble (7)
    // SFD (1)
    // *** start ethernet frame ***
    // abstract string ethDestAddr; // (6) derived as: 00000011 00000000 00000000 00000000 vvvvvvvv vvvvvvvv     
    // abstract string ethSrcAddr; // (6) derived as: 00000010 00000000 00000000 nnnnnnnn eeeeeeee iii00000
    // type (2) - always IPv4
    // payload (46-1500)
    // FCS (4)
    // *** end ethernet frame ***
    // IFG (12)

    // *** start ip layer ***  
    // length, frag control, checksum not modeled - (12)
    // abstract string ipSrcAddress; // (4) derived as : 00001010 nnnnnnnn eeeeeeee xxxppppp
    // abstract string ipDestAddress; // (4) derived as: 11100000 11100000 vvvvvvvv vvvvvvvv 
    // *** end ip layer ***
      
    // *** start udp header ***
    int udpSrcPort;    // (2)
    int udpDestPort;   // (2)
    // payload length - not modeled (2)
    // CRC - not modeled (2)
    // *** end udp header ***
    
}
