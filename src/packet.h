/*****************************************************************************
Copyright � 2001 - 2007, The Board of Trustees of the University of Illinois.
All Rights Reserved.

UDP-based Data Transfer Library (UDT) version 4

National Center for Data Mining (NCDM)
University of Illinois at Chicago
http://www.ncdm.uic.edu/

UDT is free software; you can redistribute it and/or modify it under the
terms of the GNU Lesser General Public License as published by the Free
Software Foundation; either version 3 of the License, or (at your option)
any later version.

UDT is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

/*****************************************************************************
This header file contains the definition of UDT packet structure and operations.
*****************************************************************************/

/*****************************************************************************
written by
   Yunhong Gu [gu@lac.uic.edu], last updated 08/28/2007
*****************************************************************************/

#ifndef __UDT_PACKET_H__
#define __UDT_PACKET_H__


#include "common.h"
#include "udt.h"


class CChannel;


class CPacket
{
friend class CChannel;
friend class CSndQueue;
friend class CRcvQueue;

public:
   int32_t& m_iSeqNo;                   // alias: sequence number
   int32_t& m_iMsgNo;                   // alias: message number
   int32_t& m_iTimeStamp;               // alias: timestamp
   int32_t& m_iID;			// alias: socket ID
   char*& m_pcData;                     // alias: data/control information

   static const int m_iPktHdrSize;	// packet header size

public:
   CPacket();
   ~CPacket();

      // Functionality:
      //    Get the payload or the control information field length.
      // Parameters:
      //    None.
      // Returned value:
      //    the payload or the control information field length.

   int getLength() const;

      // Functionality:
      //    Set the payload or the control information field length.
      // Parameters:
      //    0) [in] len: the payload or the control information field length.
      // Returned value:
      //    None.

   void setLength(const int& len);

      // Functionality:
      //    Pack a Control packet.
      // Parameters:
      //    0) [in] pkttype: packet type filed.
      //    1) [in] lparam: pointer to the first data structure, explained by the packet type.
      //    2) [in] rparam: pointer to the second data structure, explained by the packet type.
      //    3) [in] size: size of rparam, in number of bytes;
      // Returned value:
      //    None.

   void pack(const int& pkttype, void* lparam = NULL, void* rparam = NULL, const int& size = 0);

      // Functionality:
      //    Read the packet vector.
      // Parameters:
      //    None.
      // Returned value:
      //    Pointer to the packet vector.

   iovec* getPacketVector();

      // Functionality:
      //    Read the packet flag.
      // Parameters:
      //    None.
      // Returned value:
      //    packet flag (0 or 1).

   int getFlag() const;

      // Functionality:
      //    Read the packet type.
      // Parameters:
      //    None.
      // Returned value:
      //    packet type filed (000 ~ 111).

   int getType() const;

      // Functionality:
      //    Read the extended packet type.
      // Parameters:
      //    None.
      // Returned value:
      //    extended packet type filed (0x000 ~ 0xFFF).

   int getExtendedType() const;

      // Functionality:
      //    Read the ACK-2 seq. no.
      // Parameters:
      //    None.
      // Returned value:
      //    packet header field (bit 16~31).

   int32_t getAckSeqNo() const;

      // Functionality:
      //    Read the message boundary flag bit.
      // Parameters:
      //    None.
      // Returned value:
      //    packet header field [1] (bit 0~1).

   int getMsgBoundary() const;

      // Functionality:
      //    Read the message inorder delivery flag bit.
      // Parameters:
      //    None.
      // Returned value:
      //    packet header field [1] (bit 2).

   bool getMsgOrderFlag() const;

      // Functionality:
      //    Read the message sequence number.
      // Parameters:
      //    None.
      // Returned value:
      //    packet header field [1] (bit 3~31).

   int32_t getMsgSeq() const;

      // Functionality:
      //    Clone this packet.
      // Parameters:
      //    None.
      // Returned value:
      //    Pointer to the new packet.

   CPacket* clone() const;

protected:
   uint32_t m_nHeader[4];               // The 128-bit header field
   iovec m_PacketVector[2];             // The 2-demension vector of UDT packet [header, data]

   int32_t __pad;

protected:
   void operator = (const CPacket&) {}
};

////////////////////////////////////////////////////////////////////////////////

struct CHandShake
{
   int32_t m_iVersion;          // UDT version
   int32_t m_iType;             // UDT socket type
   int32_t m_iISN;              // random initial sequence number
   int32_t m_iMSS;              // maximum segment size
   int32_t m_iFlightFlagSize;   // flow control window size
   int32_t m_iReqType;          // connection request type: 1: regular connection request, 0: rendezvous connection request, -1/-2: response
   int32_t m_iID;		// socket ID
};


#endif
