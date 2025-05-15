# Weather App

A simple GTK application for Linux that retrieves weather information based on location or postcode.

## Features

- Enter a location name or postcode to get current weather information
- Displays temperature, condition, humidity, and wind information
- Clean and simple GTK interface

## Prerequisites

You need to have the following dependencies installed:

```bash
# On Debian/Ubuntu:
sudo apt-get install libgtk-3-dev libcurl4-openssl-dev libjson-c-dev

# On Fedora:
sudo dnf install gtk3-devel libcurl-devel json-c-devel

# On Arch Linux:
sudo pacman -S gtk3 curl json-c
```

## Building the Application

1. Clone or download this repository
2. Navigate to the project directory
3. Run `make` to build the application

```bash
make
```

## Running the Application

After building, you can run the application with:

```bash
./weather-app
```

## API Key

This application uses the [WeatherAPI.com](https://www.weatherapi.com/) service. You need to:

1. Sign up for a free API key at [WeatherAPI.com](https://www.weatherapi.com/)
2. Replace `YOUR_API_KEY` in `xnew.c` with your actual API key before building

## License

This project is provided as open-source software.
