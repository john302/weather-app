#include <gtk/gtk.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t size;
} MemoryStruct;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;
    
    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "Not enough memory\n");
        return 0;
    }
    
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;
    
    return realsize;
}

// Display weather information in the text view
static void display_weather_info(GtkTextBuffer *buffer, const char *json_string) {
    struct json_object *parsed_json;
    struct json_object *location, *current, *condition;
    struct json_object *location_name, *location_region, *location_country;
    struct json_object *temp_c, *condition_text;
    struct json_object *humidity, *wind_kph, *wind_dir;
    
    parsed_json = json_tokener_parse(json_string);
    
    if (!parsed_json || json_object_is_type(parsed_json, json_type_string)) {
        gtk_text_buffer_set_text(buffer, "Failed to parse weather data", -1);
        return;
    }
    
    if (!json_object_object_get_ex(parsed_json, "location", &location) ||
        !json_object_object_get_ex(parsed_json, "current", &current)) {
        gtk_text_buffer_set_text(buffer, "Invalid weather data format", -1);
        json_object_put(parsed_json);
        return;
    }
    
    json_object_object_get_ex(location, "name", &location_name);
    json_object_object_get_ex(location, "region", &location_region);
    json_object_object_get_ex(location, "country", &location_country);
    json_object_object_get_ex(current, "temp_c", &temp_c);
    json_object_object_get_ex(current, "humidity", &humidity);
    json_object_object_get_ex(current, "wind_kph", &wind_kph);
    json_object_object_get_ex(current, "wind_dir", &wind_dir);
    json_object_object_get_ex(current, "condition", &condition);
    json_object_object_get_ex(condition, "text", &condition_text);
    
    char weather_text[1024];
    snprintf(weather_text, sizeof(weather_text),
             "Location: %s, %s, %s\n"
             "Temperature: %.1f°C\n"
             "Condition: %s\n"
             "Humidity: %d%%\n"
             "Wind: %.1f km/h %s",
             json_object_get_string(location_name),
             json_object_get_string(location_region),
             json_object_get_string(location_country),
             json_object_get_double(temp_c),
             json_object_get_string(condition_text),
             json_object_get_int(humidity),
             json_object_get_double(wind_kph),
             json_object_get_string(wind_dir));
    
    gtk_text_buffer_set_text(buffer, weather_text, -1);
    json_object_put(parsed_json);
}

// Fetch weather data for the given location
static void fetch_weather(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "entry"));
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(widget), "buffer"));
    
    const char *location = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(location) == 0) {
        gtk_text_buffer_set_text(buffer, "Please enter a location or postcode", -1);
        return;
    }
    
    // Your API key from weatherapi.com
    const char *api_key = "499a981c3264414189312036251505"; // Replace with your actual API key
    
    char url[512];
    snprintf(url, sizeof(url), "http://api.weatherapi.com/v1/current.json?key=%s&q=%s&aqi=no", 
             api_key, location);
    
    CURL *curl_handle;
    CURLcode res;
    MemoryStruct chunk;
    
    chunk.data = malloc(1);
    chunk.size = 0;
    
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        res = curl_easy_perform(curl_handle);
        
        if (res != CURLE_OK) {
            gtk_text_buffer_set_text(buffer, "Failed to fetch weather data", -1);
        } else {
            display_weather_info(buffer, chunk.data);
        }
        
        curl_easy_cleanup(curl_handle);
    }
    
    curl_global_cleanup();
    free(chunk.data);
}
 
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    
    // Create a new window
    window = gtk_application_window_new(app);#include <gtk/gtk.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *data;
    size_t size;
} MemoryStruct;

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    MemoryStruct *mem = (MemoryStruct *)userp;
    
    char *ptr = realloc(mem->data, mem->size + realsize + 1);
    if (!ptr) {
        fprintf(stderr, "Not enough memory\n");
        return 0;
    }
    
    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->data[mem->size] = 0;
    
    return realsize;
}

// Display weather information in the text view
static void display_weather_info(GtkTextBuffer *buffer, const char *json_string) {
    struct json_object *parsed_json;
    struct json_object *location, *current, *condition;
    struct json_object *location_name, *location_region, *location_country;
    struct json_object *temp_c, *condition_text;
    struct json_object *humidity, *wind_kph, *wind_dir;
    
    parsed_json = json_tokener_parse(json_string);
    
    if (!parsed_json || json_object_is_type(parsed_json, json_type_string)) {
        gtk_text_buffer_set_text(buffer, "Failed to parse weather data", -1);
        return;
    }
    
    if (!json_object_object_get_ex(parsed_json, "location", &location) ||
        !json_object_object_get_ex(parsed_json, "current", &current)) {
        gtk_text_buffer_set_text(buffer, "Invalid weather data format", -1);
        json_object_put(parsed_json);
        return;
    }
    
    json_object_object_get_ex(location, "name", &location_name);
    json_object_object_get_ex(location, "region", &location_region);
    json_object_object_get_ex(location, "country", &location_country);
    json_object_object_get_ex(current, "temp_c", &temp_c);
    json_object_object_get_ex(current, "humidity", &humidity);
    json_object_object_get_ex(current, "wind_kph", &wind_kph);
    json_object_object_get_ex(current, "wind_dir", &wind_dir);
    json_object_object_get_ex(current, "condition", &condition);
    json_object_object_get_ex(condition, "text", &condition_text);
    
    char weather_text[1024];
    snprintf(weather_text, sizeof(weather_text),
             "Location: %s, %s, %s\n"
             "Temperature: %.1f°C\n"
             "Condition: %s\n"
             "Humidity: %d%%\n"
             "Wind: %.1f km/h %s",
             json_object_get_string(location_name),
             json_object_get_string(location_region),
             json_object_get_string(location_country),
             json_object_get_double(temp_c),
             json_object_get_string(condition_text),
             json_object_get_int(humidity),
             json_object_get_double(wind_kph),
             json_object_get_string(wind_dir));
    
    gtk_text_buffer_set_text(buffer, weather_text, -1);
    json_object_put(parsed_json);
}

// Fetch weather data for the given location
static void fetch_weather(GtkWidget *widget, gpointer data) {
    GtkWidget *entry = GTK_WIDGET(g_object_get_data(G_OBJECT(widget), "entry"));
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(g_object_get_data(G_OBJECT(widget), "buffer"));
    
    const char *location = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(location) == 0) {
        gtk_text_buffer_set_text(buffer, "Please enter a location or postcode", -1);
        return;
    }
    
    // Your API key from weatherapi.com
    const char *api_key = "YOUR_API_KEY_HERE"; // Replace with your actual API key
    
    char url[512];
    snprintf(url, sizeof(url), "http://api.weatherapi.com/v1/current.json?key=%s&q=%s&aqi=no", 
             api_key, location);
    
    CURL *curl_handle;
    CURLcode res;
    MemoryStruct chunk;
    
    chunk.data = malloc(1);
    chunk.size = 0;
    
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    
    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
        
        res = curl_easy_perform(curl_handle);
        
        if (res != CURLE_OK) {
            gtk_text_buffer_set_text(buffer, "Failed to fetch weather data", -1);
        } else {
            display_weather_info(buffer, chunk.data);
        }
        
        curl_easy_cleanup(curl_handle);
    }
    
    curl_global_cleanup();
    free(chunk.data);
}
 
static void activate(GtkApplication *app, gpointer user_data) {
    GtkWidget *window;
    GtkWidget *grid;
    GtkWidget *label;
    GtkWidget *entry;
    GtkWidget *button;
    GtkWidget *scrolled_window;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;
    
    // Create a new window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Weather App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    // Create a grid layout
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    // Create a label
    label = gtk_label_new("Enter location or postcode:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    
    // Create an entry
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
    
    // Create a button
    button = gtk_button_new_with_label("Get Weather");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);
    
    // Create a scrolled window
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 1, 3, 1);
    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    
    // Create a text view
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    
    // Get the buffer
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "Enter a location or postcode and click 'Get Weather'", -1);
    
    // Connect the button click signal
    g_object_set_data(G_OBJECT(button), "entry", entry);
    g_object_set_data(G_OBJECT(button), "buffer", buffer);
    g_signal_connect(button, "clicked", G_CALLBACK(fetch_weather), NULL);
    
    // Show all widgets
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.example.weather", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
    gtk_window_set_title(GTK_WINDOW(window), "Weather App");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    
    // Create a grid layout
    grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_container_add(GTK_CONTAINER(window), grid);
    
    // Create a label
    label = gtk_label_new("Enter location or postcode:");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 1, 1);
    
    // Create an entry
    entry = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), entry, 1, 0, 1, 1);
    
    // Create a button
    button = gtk_button_new_with_label("Get Weather");
    gtk_grid_attach(GTK_GRID(grid), button, 2, 0, 1, 1);
    
    // Create a scrolled window
    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_grid_attach(GTK_GRID(grid), scrolled_window, 0, 1, 3, 1);
    gtk_widget_set_hexpand(scrolled_window, TRUE);
    gtk_widget_set_vexpand(scrolled_window, TRUE);
    
    // Create a text view
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);
    
    // Get the buffer
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_buffer_set_text(buffer, "Enter a location or postcode and click 'Get Weather'", -1);
    
    // Connect the button click signal
    g_object_set_data(G_OBJECT(button), "entry", entry);
    g_object_set_data(G_OBJECT(button), "buffer", buffer);
    g_signal_connect(button, "clicked", G_CALLBACK(fetch_weather), NULL);
    
    // Show all widgets
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    GtkApplication *app;
    int status;
    
    app = gtk_application_new("org.example.weather", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    
    return status;
}
