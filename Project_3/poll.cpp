#include <iostream>
#include <string>

bool isValidStateCode(std::string stateCode) {
    // Capitalize input
    stateCode[0] = toupper(stateCode[0]);
    stateCode[1] = toupper(stateCode[1]);

    const std::string codes =
        "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
        "LA.ME.MA.MD.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
        "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == std::string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != std::string::npos);  // match found
}

bool isValidPartyResult(std::string partyResult) {
    for (int i = 0; i < partyResult.size();) {
        if (isdigit(partyResult[i]) &&
            isdigit(partyResult[i+1]) &&
            isalpha(partyResult[i+2])) // Check if result starts with two digits then a char, as in: 08R
        {
            i += 3; // move to the next group of characters
            continue;
        }
        else if (isdigit(partyResult[i]) && 
                 isalpha(partyResult[i+1]))  // Check if result starts with one digits then a char, as in: 3D
        {
            i += 2; // move to the next group of characters
            continue;
        }
        else // not a valid party result.
            return false;
    }
    return true;
}

bool isValidPollString(std::string pollData) {
    if (pollData.back() == ',') // deal with the annoying comma at end case.
        return false;

    bool isValid = true; // default to true

    int pos = 0;
    std::string stateForcast;
    while (pollData != "") {
        if ((pos = pollData.find(',')) != std::string::npos) { // found commas, so must have multiple forecasts.
            stateForcast = pollData.substr(0, pos); // Our state forecast
            pollData.erase(0, pos + 1); // erase the forecast and comma from pollData
        }
        else { // no commas, so only one forecast left.
            stateForcast = pollData;
            pollData.erase(); // leave the loop
        }

        std::string stateCode = stateForcast.substr(0, 2);

        if (!isValidStateCode(stateCode)) {
            isValid = false; // bad state code.
            break;
        }

        std::string partyResult = stateForcast.erase(0, 2);
        if (!isValidPartyResult(partyResult)) {
            isValid = false; // bad party result
            break;
        }
}

    return isValid;
}

int countSeats(std::string pollData, char party, int seatCount) {
    if (!isValidPollString(pollData))
        return 1; // invalid poll string
    if (!isalpha(party))
        return 2; // party isn't a character

    seatCount = 0;
    for (int i = 0; i < pollData.size(); i++) {
        if (toupper(pollData[i]) == toupper(party)) { // only care about specific party seats
            if (
                isdigit(pollData[i - 1]) &&
                isdigit(pollData[i - 2])) // party char is preceded by two numbers
            {   // convert two digit characters to integer and add to seatCount
                seatCount += std::stoi(std::string() + pollData[i - 2] + pollData[i - 1]);
            }
            else if (isdigit(pollData[i - 1])) // single digit, convert to integer and add to seatCount
                seatCount += std::stoi(std::string() + pollData[i - 1]); 
        }
    }
    std::cout << seatCount << std::endl;
    return 0;
}

int main() {}