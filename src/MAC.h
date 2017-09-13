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

#ifndef __MAC_H__
#define __MAC_H__

#include "queueinglib/IServer.h"
#include "queueinglib/SelectionStrategies.h"

namespace afdx {

/**
 * A full duplex Ethernet MAC module
 */
class MAC : public cSimpleModule, public queueing::IServer
{
  private:
    queueing::SelectionStrategy *selectionStrategy;
    bool reserved;
    simtime_t max_frame_age;
    cMessage *endServiceMsg;

  protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);

  public:
      MAC();
      virtual ~MAC();
      virtual bool isIdle();
      virtual void reserve();
};

}; // namespace afdx

#endif
