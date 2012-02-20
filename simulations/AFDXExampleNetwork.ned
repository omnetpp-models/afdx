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

import afdx.Switch;
import afdx.EndSystem;
import afdx.Eth100;
//
// TODO auto-generated module
//
network AFDXExampleNetwork
{
    @display("bgb=356,250;i=block/network2");
    submodules:
        switchA: Switch {
            @display("p=180,52");
        }
        ES0: EndSystem {
            @display("p=76,52");
        }
        ES1: EndSystem {
            @display("p=76,192");
        }
        ES2: EndSystem {
            @display("p=276,192");
        }
        ES3: EndSystem {
            @display("p=276,52");
        }
        switchB: Switch {
            @display("p=180,192");
        }
    connections allowunconnected:
        ES0.ethPortA <--> Eth100 <--> switchA.ethPort[0];
        ES1.ethPortA <--> Eth100 <--> switchA.ethPort[1];
        ES2.ethPortA <--> Eth100 <--> switchA.ethPort[2];
        ES3.ethPortA <--> Eth100 <--> switchA.ethPort[3];
        ES0.ethPortB <--> Eth100 <--> switchB.ethPort[0];
        ES1.ethPortB <--> Eth100 <--> switchB.ethPort[1];
        ES2.ethPortB <--> Eth100 <--> switchB.ethPort[2];
        ES3.ethPortB <--> Eth100 <--> switchB.ethPort[3];
}
