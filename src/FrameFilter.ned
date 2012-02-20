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
// Filter received packets
// 
// The frame size is verified to be within the defined limits of VL length (between SMIN and LMAX/SMAX).
// The frame is verified to have an integer number of bytes to check alignment.
// The FCS for the frame is calculated and verified against the value contained in the frame.
// The incoming switch port assignment for the VL is verified.
// The destination MAC addressed for the VL is verified as reachable.

simple FrameFilter
{
    @display("i=block/filter");
    gates:
        input in;
        output out;
}
