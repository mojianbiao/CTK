/*=============================================================================

  Library: CTK

  Copyright (c) 2010 German Cancer Research Center,
    Division of Medical and Biological Informatics

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=============================================================================*/

#include "ctkSoapMessageProcessorList.h"

void ctkSoapMessageProcessorList::push_back( const ctkSoapMessageProcessor& processor )
{
	processors.push_back( processor );
}

void ctkSoapMessageProcessorList::remove( const ctkSoapMessageProcessor& processor )
{
	processors.remove( processor );
}

bool ctkSoapMessageProcessorList::process(
	const QtSoapMessage& message,
	QtSoapMessage* reply ) const
{
  for( std::list<ctkSoapMessageProcessor>::const_iterator it = processors.begin(); 
    it != processors.end(); it++)
	{
		if( it->process( message, reply ) )
		{
			return true;
		}
	}
	// if still here, no processor could process the message
	reply->setFaultCode( QtSoapMessage::Server );
    reply->setFaultString( "No processor found to process message." );
	return false;
}
		
