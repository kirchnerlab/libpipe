{
    "connections": [
        {
            "filterName": "Source1",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication2a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication3a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication4a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication21a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication1a"
                },
                {
                    "precursorName": "Multiplication2a"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication1a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication2a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication22a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication3a"
                },
                {
                    "precursorName": "Multiplication4a"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication3a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication4a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication31a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication21a"
                },
                {
                    "precursorName": "Multiplication22a"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication21a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication22a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication1b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication2b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication3b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication4b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication21b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication1b"
                },
                {
                    "precursorName": "Multiplication2b"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication1b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication2b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication22b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication3b"
                },
                {
                    "precursorName": "Multiplication4b"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication3b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication4b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication31b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication21b"
                },
                {
                    "precursorName": "Multiplication22b"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication21b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication22b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication1c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication2c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication3c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication4c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication21c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication1c"
                },
                {
                    "precursorName": "Multiplication2c"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication1c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication2c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication22c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication3c"
                },
                {
                    "precursorName": "Multiplication4c"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication3c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication4c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication31c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication21c"
                },
                {
                    "precursorName": "Multiplication22c"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication21c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication22c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication1d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication2d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication3d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication4d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1"
                },
                {
                    "precursorName": "Source1"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source1",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication21d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication1d"
                },
                {
                    "precursorName": "Multiplication2d"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication1d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication2d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication22d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication3d"
                },
                {
                    "precursorName": "Multiplication4d"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication3d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication4d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Multiplication31d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Multiplication21d"
                },
                {
                    "precursorName": "Multiplication22d"
                }
            ],
            "ports": [
                {
                    "filterName": "Multiplication21d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Multiplication22d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn2"
                }
            ]
        
        },
        {
            "filterName": "Handler",
            "identifier": "Handler",
            "precursors": [
                {
                    "precursorName": "Multiplication31a"
                },
                {
                    "precursorName": "Multiplication31b"
                },
                {
                    "precursorName": "Multiplication31c"
                },
                {
                    "precursorName": "Multiplication31d"
                }
            ],
            "ports": [
            ]
        
        }
    ]
}