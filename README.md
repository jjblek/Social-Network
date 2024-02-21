# Project 1

Generate a Social Network

## Description

* Parse a JSON file of users
* Construct a Social Network from parsed JSON
* Generate HTML files representing the Social Network

## Getting Started

### Executing program

* Generate a JSON user file if one is not provided
```
python -u "input_gen.py" > input.json
```
* Execute program
```
make
./SocialNetwork.x input.json
```
### Program Arguments
* Generate CSS file: -css
* Generate Log file: -log
```
./SocialNetwork.x input.json -css -log
```