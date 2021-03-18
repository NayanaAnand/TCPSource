/*
 * This file is protected by Copyright. Please refer to the COPYRIGHT file distributed with this 
 * source distribution.
 * 
 * This file is part of REDHAWK Basic Components sourcesocket.
 * 
 * REDHAWK Basic Components sourcesocket is free software: you can redistribute it and/or modify it under the terms of 
 * the GNU Lesser General Public License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 * 
 * REDHAWK Basic Components sourcesocket is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
 * PURPOSE.  See the GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License along with this 
 * program.  If not, see http://www.gnu.org/licenses/.
 */

#ifndef VECTORSWAP_H_
#define VECTORSWAP_H_

#include <byteswap.h>
#include <vector>
#include <algorithm>

//in place byte swap
template<typename T, typename U> void vectorSwap(std::vector<T, U>& dataVec, const unsigned char numBytes)
{
	if (numBytes>1)
	{
		size_t totalBytes = dataVec.size()*sizeof(T);
		assert(totalBytes%numBytes==0);
		size_t numSwap = totalBytes/numBytes;
		if (numBytes==2)
		{
			uint16_t* p = reinterpret_cast< uint16_t* >(&dataVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*p = bswap_16(*p);
				p++;
			}
		} else if (numBytes==4)
		{
			uint32_t* p = reinterpret_cast< uint32_t* >(&dataVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*p = bswap_32(*p);
				p++;
			}
		} else if(numBytes==8)
		{
			uint64_t* p = reinterpret_cast< uint64_t* >(&dataVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*p = bswap_64(*p);
				p++;
			}
		}else
		{
			//explicitly swap all the bytes out by hand if we don't have a good optimized macro available for us
			char* next = reinterpret_cast< char* >(&dataVec[0]);
			char* first;
			char* second;
			for (size_t i=0; i!=numSwap; i++)
			{
				first = next;
				next = first+numBytes;
				second = next;
				std::reverse(first, second);
			}
		}
	}
}

//non in place vector byte swap
template<typename T, typename U> void vectorSwap(const char* data, std::vector<T, U>& outVec, const unsigned char numBytes)
{
	if (numBytes>1)
	{
		size_t totalBytes = outVec.size()*sizeof(T);
		assert(totalBytes%numBytes==0);
		size_t numSwap = totalBytes/numBytes;
		if (numBytes==2)
		{
			const uint16_t* from = reinterpret_cast<const uint16_t* >(data);
			uint16_t* to = reinterpret_cast< uint16_t* >(&outVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*to = bswap_16(*from);
				to++;
				from++;
			}
		} else if (numBytes==4)
		{
			const uint32_t* from = reinterpret_cast<const uint32_t* >(data);
			uint32_t* to = reinterpret_cast< uint32_t* >(&outVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*to = bswap_32(*from);
				to++;
				from++;
			}
		} else if(numBytes==8)
		{
			const uint64_t* from = reinterpret_cast<const uint64_t* >(data);
			uint64_t* to = reinterpret_cast< uint64_t* >(&outVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				*to = bswap_64(*from);
				to++;
				from++;
			}
		}else
		{
			//explicitly swap all the bytes out by hand if we don't have a good optimized macro available for us
			const char* next = reinterpret_cast<const char* >(data);
			const char* first;
			char* to = reinterpret_cast< char* >(&outVec[0]);
			for (size_t i=0; i!=numSwap; i++)
			{
				first = next;
				next+=numBytes;
				std::reverse_copy(first, next, to);
				to+=numBytes;
			}
		}
	}
}


#endif /* VECTORSWAP_H_ */
