bool run;
byte pos,trip;
const byte relayPin[4] = { 10,11,12,13 };

void setup()
{
	pos = 0;
	trip = 0;

	for (int i = 0; i < 4; i++)
	{
		pinMode(relayPin[i], OUTPUT);
	}

	Serial.begin(9600);
	Serial.setTimeout(50);
}

void EnableR(byte pin, byte state)
{
	digitalWrite(relayPin[pin], state);
}

void loop()
{
	if (Serial.available()) {

		byte data[2];

		Serial.readBytes(data, 2);

		//TEST MODE
		if (data[0] == 0x63) {
			run = true;
		}
		else {
			EnableR(data[0], data[1]);
		}
	}

	if (run)
	{
		if (trip == 2) {
			run = false;
			trip = 0;
			return;
		}

		switch (pos)
		{
		case 0:
			digitalWrite(relayPin[3], LOW);
			digitalWrite(relayPin[0], HIGH);
			break;
		case 1:
			digitalWrite(relayPin[0], LOW);
			digitalWrite(relayPin[1], HIGH);
			break;
		case 2:
			digitalWrite(relayPin[1], LOW);
			digitalWrite(relayPin[2], HIGH);
			break;
		case 3:
			digitalWrite(relayPin[2], LOW);
			digitalWrite(relayPin[3], HIGH);
			trip++;
			break;
		}

		if (pos < 3)
		{
			pos++;
		}
		else if (pos == 3)
		{
			pos = 0;
		}

		delay(500);
	}
	else
	{
		delay(100);
	}

}
