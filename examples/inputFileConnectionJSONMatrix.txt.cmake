{
    "connections": [
        {
            "filterName": "Source1a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source2a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source3a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source4a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source5a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source6a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source7a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source8a",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1a",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1a"
                },
                {
                    "precursorName": "Source2a"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source2a",
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
                    "precursorName": "Source3a"
                },
                {
                    "precursorName": "Source4a"
                }
            ],
            "ports": [
                {
                    "filterName": "Source3a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source4a",
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
                    "precursorName": "Source5a"
                },
                {
                    "precursorName": "Source6a"
                }
            ],
            "ports": [
                {
                    "filterName": "Source5a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source6a",
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
                    "precursorName": "Source7a"
                },
                {
                    "precursorName": "Source8a"
                }
            ],
            "ports": [
                {
                    "filterName": "Source7a",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source8a",
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
            "filterName": "Source1b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source2b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source3b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source4b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source5b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source6b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source7b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source8b",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1b",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1b"
                },
                {
                    "precursorName": "Source2b"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source2b",
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
                    "precursorName": "Source3b"
                },
                {
                    "precursorName": "Source4b"
                }
            ],
            "ports": [
                {
                    "filterName": "Source3b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source4b",
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
                    "precursorName": "Source5b"
                },
                {
                    "precursorName": "Source6b"
                }
            ],
            "ports": [
                {
                    "filterName": "Source5b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source6b",
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
                    "precursorName": "Source7b"
                },
                {
                    "precursorName": "Source8b"
                }
            ],
            "ports": [
                {
                    "filterName": "Source7b",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source8b",
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
            "filterName": "Source1c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source2c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source3c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source4c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source5c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source6c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source7c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source8c",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1c",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1c"
                },
                {
                    "precursorName": "Source2c"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source2c",
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
                    "precursorName": "Source3c"
                },
                {
                    "precursorName": "Source4c"
                }
            ],
            "ports": [
                {
                    "filterName": "Source3c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source4c",
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
                    "precursorName": "Source5c"
                },
                {
                    "precursorName": "Source6c"
                }
            ],
            "ports": [
                {
                    "filterName": "Source5c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source6c",
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
                    "precursorName": "Source7c"
                },
                {
                    "precursorName": "Source8c"
                }
            ],
            "ports": [
                {
                    "filterName": "Source7c",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source8c",
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
            "filterName": "Source1d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source2d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source3d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source4d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source5d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source6d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source7d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Source8d",
            "identifier": "Source",
            "precursors": [],
            "ports": []
        },
        {
            "filterName": "Multiplication1d",
            "identifier": "MatrixMulAlgorithm",
            "precursors": [
                {
                    "precursorName": "Source1d"
                },
                {
                    "precursorName": "Source2d"
                }
            ],
            "ports": [
                {
                    "filterName": "Source1d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source2d",
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
                    "precursorName": "Source3d"
                },
                {
                    "precursorName": "Source4d"
                }
            ],
            "ports": [
                {
                    "filterName": "Source3d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source4d",
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
                    "precursorName": "Source5d"
                },
                {
                    "precursorName": "Source6d"
                }
            ],
            "ports": [
                {
                    "filterName": "Source5d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source6d",
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
                    "precursorName": "Source7d"
                },
                {
                    "precursorName": "Source8d"
                }
            ],
            "ports": [
                {
                    "filterName": "Source7d",
                    "portNameOfFilter": "MatrixOut",
                    "portNameOfThis": "MatrixIn1"
                },
                {
                    "filterName": "Source8d",
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