uint8_t SPI_transfer(uint8_t data_input, uint8_t *data_output)
{
	uint8_t test, timeout;
	timeout = 0;
	SPDAT = data_input;
	do
	{
		test = SPSTA; // SPDAT?
		timeout++;
	}while(((test & 0xF0) != 0xF0)&&(timeout!=0));
	if(timeout != 0)
	{
		*data_output = SPDAT;
		timeout = (test & 0x70);
	}
	else
	{
		timeout = TIMEOUT_ERROR;
	}
	return timeout;
}


uint8_t send_command(uint8_t cmd, uint32_t argum);
{
	uint8_t error_flag, send_val, return_val, index;
	if(cmd < 64)
	{
		send_val = 0x40 | cmd;
		error_flag = SPI_transfer(send_val, &return_val);
		index = 24;
		while((error_flag == NO_ERRORS)&(index<25)
		{
			send_val = (uint8_t)(argum >> index);
			error_flag = SPI_transfer(send_val, &return_val);
			index -= 8;
		}
		if(cmd == 0)
			send_val = 0x95;
		else if(cmd == 8)
			send_val = 0x87;
		else
			send_val = 0x01;
		if(error_flag == NO_ERRORS)
			error_flag = SPI_transfer(send_val, &return_val);
		if(error_flag == NO_ERRORS)
			error_flag = SPI_ERROR;
	}
	else
		error_flag = ILLEGAL_COMMAND;
	return error_flag;
}


uint8_t get_response(uint8_t num_bytes, uint8_t *array_out)
{
	uint8_t timeout, error_flag;
	timeout = 0;
	error_flag = NO_ERRORS;
	do
	{
		error_flag = SPI_transfer(0xFF, &recieve_value)
		timeout++;
	}while((timeout!=0)&&(error_flag == NO_ERRORS)&&(receive_val == 0xFF));
	*array_out = receive_value;
	if(timeout == 0)
		error_flag = TIMEOUT_ERROR;
	else if(error_flag != NO_ERRORS)
		error_flag = SPI_ERROR;
	else if((receive_value != 0x01)||(recieve_value != 0x00))
		error_flag = SPI_ERROR;
	else if(num_bytes > 1)
	{
		for(index = 1; index < num_bytes; index++)
		{
			SPI_transfer(0xFF, & recieve_value);
			array_out[index] = recieve_value;
		}
	}
	SPI_transfer(0xFF, &recieve_value);
	return error_flag;
}
