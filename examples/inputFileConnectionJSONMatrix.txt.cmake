{
    "connections": [
        {
            "filterName": "Source1",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source2",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source3",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source4",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source5",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source6",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source7",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source8",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source2"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source2",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication2",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source3"
                },
                {
                    "precursorName": "Source4"
                }
            ],
            "ports": [
                {
                    "filterName": "Source3",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source4",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication3",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source5"
                },
                {
                    "precursorName": "Source6"
                }
            ],
            "ports": [
                {
                    "filterName": "Source5",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source6",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication4",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source7"
                },
                {
                    "precursorName": "Source8"
                }
            ],
            "ports": [
                {
                    "filterName": "Source7",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source8",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication21",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication1"
                },
                {
                    "precursorName": "Multiplication2"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication2",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication22",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication3"
                },
                {
                    "precursorName": "Multiplication4"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication3",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication4",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication31",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication21"
                },
                {
                    "precursorName": "Multiplication22"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication21",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication22",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        }
    ]
}