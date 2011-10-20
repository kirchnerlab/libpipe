// An example configuration file that stores information Filters.

@include "inputFile2Filter.txt"
// Connect Filters:
connections =
(
   { filterName  = "Lowercase";
     identifier = "LowercaseFilter";
     precursors = ( {precursorName="Combiner"}
     )
     ports = (
     	{filterName="Combiner";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },
   
   { filterName  = "Source";
     identifier = "SourceFilter";
     precursors = ()
     ports = ()
   },
   
   { filterName  = "Uppercase";
     identifier = "UppercaseFilter";
     precursors = ( {precursorName="Source"}
     )
     ports = (
     	{filterName="Source";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },
   
   { filterName  = "ROTDecrypter";
     identifier = "ROTFilter";
     precursors = ( {precursorName="Uppercase"}
     )
     ports = (
     	{filterName="Uppercase";
     	 portNameOfFilter="StringOutput";
     	 portNameOfThis="StringInput";
     	}
     )
   },     
   
   { filterName  = "ROTDecrypter1";
     identifier = "ROTFilter";
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
     identifier = "CombinerFilter";
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
		{filterName="Lowercase";
		requestType="UPDATE";
		requestRank=1;
		makeTrace = true;},
		
		{filterName="Lowercase";
		requestType="DELETE";
		requestRank=2;
		makeTrace=true;},
		
		{filterName="Lowercase";
		requestType="UPDATE";
		requestRank=3;
		makeTrace=true;}
);
