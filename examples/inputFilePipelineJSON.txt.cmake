{
    "pipeline": [
        {
            "filterName": "Lowercase",
            "requestType": "UPDATE",
            "requestRank": 1,
            "makeTrace": "true"
        },
        {
            "filterName": "Lowercase",
            "requestType": "DELETE",
            "requestRank": 2,
            "makeTrace": "true"
        },
        {
            "filterName": "Lowercase",
            "requestType": "UPDATE",
            "requestRank": 3,
            "makeTrace": "true"
        }
    ]
}