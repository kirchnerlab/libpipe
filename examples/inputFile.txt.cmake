#6dc0a277ae36db78b3494d0ddf32dd3d
// An example configuration file that stores information Filters.

// Store filters:
filters =
(
   { filterName  = "LowercaseFilter";
     algorithmName = "LowercaseAlgorithm";
     managerName  = "MangerRTC";
     precursors = ( {precursorName="Combiner"}
     )
     ports = (
     	{filterName="Combiner";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },
   
{ filterName  = "TheSource";
     algorithmName = "Source";
     managerName  = "MangerRTC";
     precursors = ()
     ports = ()
   },
   
   { filterName  = "Filter1";
     algorithmName = "UppercaseAlgorithm";
     managerName  = "MangerRTC";
     precursors = ( {precursorName="TheSource"}
     )
     ports = (
     	{filterName="TheSource";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },
   
   { filterName  = "ROTDecrypter";
     algorithmName = "ROT13Algorithm";
     managerName  = "MangerRTC";
     precursors = ( {precursorName="Filter1"}
     )
     ports = (
     	{filterName="Filter1";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },     
   
   { filterName  = "ROTDecrypter1";
     algorithmName = "ROT13Algorithm";
     managerName  = "MangerRTC";
     precursors = ( {precursorName="ROTDecrypter"}
     )
     ports = (
     	{filterName="ROTDecrypter";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },     
   
       
    { filterName  = "Combiner";
     algorithmName = "CombineAlgorithm";
     managerName  = "MangerRTC";
     precursors = (
      				{precursorName="ROTDecrypter"},
      				{precursorName="ROTDecrypter1"}
     )
     ports = (
     	{filterName="ROTDecrypter";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput1";
     	},
     	{filterName="ROTDecrypter1";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput2";
     	} 
     )
   }
);


//Requests
request = (
		{filteName="LowercaseFilter";
		requestType="UPDATE";
		requestRank=1;
		makeTrace = true;},
		
		{filteName="ROTDecrypter";
		requestType="DELETE";
		requestRank=2;
		makeTrace=true;},
		
		{filteName="LowercaseFilter";
		requestType="UPDATE";
		requestRank=3;
		makeTrace=true;}
		

);
