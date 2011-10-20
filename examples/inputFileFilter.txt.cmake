// An example configuration file that stores information Filters.

// Store filters:
filters =
(
   { filterIdentifier  = "LowercaseFilter";
     algorithmName = "LowercaseAlgorithm";
     managerName  = "MangerRTC";
   },
   
   { filterIdentifier  = "SourceFilter";
     algorithmName = "Source";
     managerName  = "MangerRTC";
   },
   
   { filterIdentifier  = "UppercaseFilter";
     algorithmName = "UppercaseAlgorithm";
     managerName  = "MangerRTC";
   },
   
   { filterIdentifier  = "ROTFilter";
     algorithmName = "ROT13Algorithm";
     managerName  = "MangerRTC";
   },     
          
   { filterIdentifier  = "CombinerFilter";
     algorithmName = "CombineAlgorithm";
     managerName  = "MangerRTC";
   }
);
