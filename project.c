#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#define CITY_COUNT 35
#define INF INT_MAX
#define MAX_ROUTES 3
#define MAX_CRITERIA 3

// ─── Colour Macros ─────────────────────────────────────────────────────────────
#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define BOLD    "\x1b[1m"
// ────────────────────────────────────────────────────────────────────────────────

char *cities[CITY_COUNT] = {
    "Delhi", "Mumbai", "Kolkata", "Chennai", "Hyderabad",
    "Bangalore", "Jaipur", "Surat", "Lucknow", "Dehradun",
    "Ahmedabad", "Pune", "Patna", "Bhopal", "Indore",
    "Chandigarh", "Nagpur", "Ranchi", "Raipur", "Guwahati",
    "Bhubaneswar", "Thiruvananthapuram", "Kochi", "Madurai",
    "Coimbatore", "Vijayawada", "Visakhapatnam", "Vadodara",
    "Jammu", "Amritsar", "Agartala", "Imphal", "Shillong",
    "Aizawl", "Panaji"
};

enum TransportMode { TRAIN, BUS, FLIGHT };
char *modeNames[] = {"Train", "Bus", "Flight"};

struct RouteInfo {
    int distance;
    int cost;
    int time;
    enum TransportMode mode;
};

struct Node {
    int city;
    struct RouteInfo info;
    struct Node *next;
};

struct Node *graph[CITY_COUNT] = {NULL};

void addEdge(int from, int to, int distance, int cost, int time, enum TransportMode mode) {
    struct Node *newNode = malloc(sizeof(*newNode));
    newNode->city = to;
    newNode->info.distance = distance;
    newNode->info.cost = cost;
    newNode->info.time = time;
    newNode->info.mode = mode;
    newNode->next = graph[from];
    graph[from] = newNode;

    newNode = malloc(sizeof(*newNode));
    newNode->city = from;
    newNode->info.distance = distance;
    newNode->info.cost = cost;
    newNode->info.time = time;
    newNode->info.mode = mode;
    newNode->next = graph[to];
    graph[to] = newNode;
}

int getCityIndex(char *name) {
    for (int i = 0; i < CITY_COUNT; i++) {
        if (strcasecmp(name, cities[i]) == 0)
            return i;
    }
    return -1;
}

void printRoute(int path[], int pathLength, int distance, int cost, int time, int showTotals) {
    printf("\n" BOLD CYAN "Route: " RESET);
    for (int i = 0; i < pathLength; i++) {
        printf(CYAN "%s" RESET, cities[path[i]]);
        if (i != pathLength - 1) printf(" -> ");
    }
    printf("\n" BOLD YELLOW "Total Distance: " RESET "%d km\n", distance);
    printf(BOLD YELLOW "Total Cost: " RESET "Rs.%d\n", cost);
    printf(BOLD YELLOW "Total Time: " RESET "%d hrs %d mins\n", time / 60, time % 60);
}

// Modified to handle multiple criteria
void findOptimalPath(int start, int end, int criteria[], int criteriaCount) {
    int dist[CITY_COUNT], cost[CITY_COUNT], timeArr[CITY_COUNT], visited[CITY_COUNT], prev[CITY_COUNT];
    float combinedScore[CITY_COUNT];
    
    for (int i = 0; i < CITY_COUNT; i++) {
        dist[i] = INF;
        cost[i] = INF;
        timeArr[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
        combinedScore[i] = INF;
    }

    dist[start] = cost[start] = timeArr[start] = combinedScore[start] = 0;

    for (int count = 0; count < CITY_COUNT; count++) {
        float minScore = INF;
        int u = -1;
        
        for (int i = 0; i < CITY_COUNT; i++) {
            if (!visited[i] && combinedScore[i] < minScore) {
                minScore = combinedScore[i];
                u = i;
            }
        }

        if (u == -1 || u == end) break;
        visited[u] = 1;

        struct Node *temp = graph[u];
        while (temp) {
            int v = temp->city;
            int newDist = dist[u] + temp->info.distance;
            int newCost = cost[u] + temp->info.cost;
            int newTime = timeArr[u] + temp->info.time;
            
            float newScore = 0;
            for (int i = 0; i < criteriaCount; i++) {
                switch(criteria[i]) {
                    case 0: newScore += newDist; break;
                    case 1: newScore += newCost / 10.0f; break;
                    case 2: newScore += newTime / 10.0f; break;
                }
            }
            
            if (!visited[v] && newScore < combinedScore[v]) {
                dist[v] = newDist;
                cost[v] = newCost;
                timeArr[v] = newTime;
                combinedScore[v] = newScore;
                prev[v] = u;
            }
            temp = temp->next;
        }
    }

    if (dist[end] == INF) {
        printf(RED "\nNo route found between %s and %s\n" RESET, cities[start], cities[end]);
        return;
    }

    int path[CITY_COUNT], pathLength = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }
    for (int i = 0; i < pathLength/2; i++) {
        int tmp = path[i];
        path[i] = path[pathLength-1-i];
        path[pathLength-1-i] = tmp;
    }

    printf("\n" GREEN "========================================" RESET);
    printf("\n" BOLD MAGENTA "          OPTIMAL ROUTE FINDER" RESET);
    printf("\n" GREEN "========================================" RESET);
    printf("\n" BOLD "Search Criteria: " RESET);
    {
        char *names[] = {"DISTANCE", "COST", "TIME"};
        for (int i = 0; i < criteriaCount; i++) {
            printf(CYAN "%s" RESET, names[criteria[i]]);
            if (i < criteriaCount-1) printf(" " BOLD "+" RESET " ");
        }
    }
    printf("\n" BOLD "From: " RESET "%s", cities[start]);
    printf("\n" BOLD "To: " RESET "%s", cities[end]);
    printf("\n" GREEN "========================================" RESET);

    printRoute(path, pathLength, dist[end], cost[end], timeArr[end], 1);

    printf("\n" BOLD GREEN "Transport Details:\n" RESET);
    int totalDistance = 0, totalCost = 0, totalTime = 0; // Accumulate totals here
    for (int i = 0; i < pathLength - 1; i++) {
        int from = path[i], to = path[i + 1];
        struct Node *temp = graph[from];
        while (temp) {
            if (temp->city == to) {
                // Print the transport details for this segment
                printf(CYAN " " RESET "%s to %s: %s (%.1f hrs, %d km, Rs.%d)\n",
                       cities[from], cities[to], modeNames[temp->info.mode],
                       temp->info.time / 60.0, temp->info.distance, temp->info.cost);
    
                // Accumulate the totals
                totalDistance += temp->info.distance;
                totalCost += temp->info.cost;
                totalTime += temp->info.time;
                break;
            }
            temp = temp->next;
        }
    }
    printf("\n" BOLD YELLOW "Verified Totals:\n" RESET);
printf(BOLD YELLOW "Total Distance: " RESET "%d km\n", totalDistance);
printf(BOLD YELLOW "Total Cost: " RESET "Rs.%d\n", totalCost);
printf(BOLD YELLOW "Total Time: " RESET "%d hrs %d mins\n", totalTime / 60, totalTime % 60);
}    

void findRoutesWithinBudget(int start, int end, int maxBudget) {
    printf("\n" GREEN "========================================" RESET);
    printf("\n" BOLD MAGENTA "       BUDGET ROUTE FINDER (MAX Rs.%d)" RESET, maxBudget);
    printf("\n" BOLD "From: " RESET "%s", cities[start]);
    printf("\n" BOLD "To: " RESET "%s", cities[end]);
    printf("\n" GREEN "========================================" RESET);

    int dist[CITY_COUNT], cost[CITY_COUNT], time[CITY_COUNT], visited[CITY_COUNT], prev[CITY_COUNT];
    for (int i = 0; i < CITY_COUNT; i++) {
        dist[i] = INF;
        cost[i] = INF;
        time[i] = INF;
        visited[i] = 0;
        prev[i] = -1;
    }

    dist[start] = 0;
    cost[start] = 0;
    time[start] = 0;

    for (int count = 0; count < CITY_COUNT - 1; count++) {
        int minDist = INF, u = -1;
        for (int i = 0; i < CITY_COUNT; i++) {
            if (!visited[i] && dist[i] < minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1 || u == end) break;
        visited[u] = 1;

        struct Node *temp = graph[u];
        while (temp) {
            int v = temp->city;
            if (!visited[v] && cost[u] + temp->info.cost <= maxBudget) {
                int newDist = dist[u] + temp->info.distance;
                int newCost = cost[u] + temp->info.cost;
                int newTime = time[u] + temp->info.time;

                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    cost[v] = newCost;
                    time[v] = newTime;
                    prev[v] = u;
                }
            }
            temp = temp->next;
        }
    }

    if (dist[end] == INF) {
        printf(RED "\nNo routes found within Rs.%d budget\n" RESET, maxBudget);
        return;
    }

    int path[CITY_COUNT], pathLength = 0;
    for (int at = end; at != -1; at = prev[at]) {
        path[pathLength++] = at;
    }

    for (int i = 0; i < pathLength / 2; i++) {
        int temp = path[i];
        path[i] = path[pathLength - 1 - i];
        path[pathLength - 1 - i] = temp;
    }

    printf("\n" BOLD YELLOW "Shortest Route Option" RESET);
    printRoute(path, pathLength, dist[end], cost[end], time[end], 1);
}

void viewCities() {
    printf("\n" BOLD MAGENTA "Available Cities:\n" RESET);
    for (int i = 0; i < CITY_COUNT; i++) {
        printf(BOLD "%2d." RESET " " CYAN "%s\n" RESET, i + 1, cities[i]);
    }
}

void setupGraph() {
    // Train connections
    addEdge(0, 6, 280, 500, 300, TRAIN); // Delhi-Jaipur
    addEdge(0, 8, 550, 600, 420, TRAIN); // Delhi-Lucknow
    addEdge(0, 9, 280, 400, 300, BUS);    // Delhi-Dehradun
    addEdge(1, 11, 150, 300, 180, BUS);   // Mumbai-Pune
    addEdge(1, 7, 300, 450, 240, TRAIN);  // Mumbai-Surat
    addEdge(1, 4, 710, 1500, 450, TRAIN); // Mumbai-Hyderabad
    addEdge(3, 5, 350, 400, 300, TRAIN);  // Chennai-Bangalore
    addEdge(4, 25, 275, 600, 240, TRAIN); // Hyderabad-Vijayawada
    addEdge(5, 24, 360, 800, 300, BUS);   // Bangalore-Coimbatore
    addEdge(2, 20, 440, 800, 360, TRAIN); // Kolkata-Bhubaneswar
    addEdge(2, 19, 1020, 1800, 720, TRAIN); // Kolkata-Guwahati
    addEdge(10, 7, 270, 500, 240, TRAIN); // Ahmedabad-Surat
    addEdge(10, 27, 120, 300, 180, BUS);  // Ahmedabad-Vadodara
    addEdge(6, 14, 600, 900, 420, TRAIN); // Jaipur-Indore
    addEdge(14, 13, 190, 300, 150, BUS);  // Indore-Bhopal
    addEdge(12, 17, 370, 700, 300, TRAIN); // Patna-Ranchi
    addEdge(18, 16, 285, 600, 240, TRAIN); // Raipur-Nagpur
    addEdge(15, 0, 250, 500, 270, TRAIN); // Chandigarh-Delhi
    addEdge(15, 29, 230, 450, 240, TRAIN); // Chandigarh-Amritsar
    addEdge(29, 28, 210, 400, 210, BUS);  // Amritsar-Jammu
    addEdge(26, 20, 450, 900, 390, TRAIN); // Visakhapatnam-Bhubaneswar
    addEdge(23, 24, 210, 400, 240, TRAIN); // Madurai-Coimbatore
    addEdge(19, 32, 100, 250, 180, BUS);  // Guwahati-Shillong
    addEdge(9, 15, 320, 600, 240, TRAIN);   // Dehradun-Chandigarh  
addEdge(16, 18, 300, 550, 210, TRAIN);   // Nagpur-Raipur  
addEdge(17, 19, 800, 1400, 540, TRAIN);  // Ranchi-Guwahati  
addEdge(20, 26, 440, 800, 300, TRAIN);   // Bhubaneswar-Visakhapatnam  
addEdge(21, 23, 220, 400, 180, TRAIN);   // Thiruvananthapuram-Madurai  
addEdge(22, 24, 200, 350, 150, TRAIN);   // Kochi-Coimbatore  
addEdge(25, 26, 350, 600, 240, TRAIN);   // Vijayawada-Visakhapatnam  
addEdge(28, 29, 220, 450, 180, TRAIN);   // Jammu-Amritsar  
addEdge(30, 31, 300, 500, 240, TRAIN);   // Agartala-Imphal  
addEdge(32, 33, 200, 400, 180, TRAIN);   // Shillong-Aizawl  
addEdge(8, 12, 650, 1000, 480, BUS);    // Lucknow-Patna  
addEdge(11, 14, 550, 900, 360, BUS);    // Pune-Indore  
addEdge(13, 16, 400, 700, 300, BUS);    // Bhopal-Nagpur  
addEdge(19, 30, 600, 1200, 480, BUS);   // Guwahati-Agartala  
addEdge(23, 24, 180, 300, 150, BUS);    // Madurai-Coimbatore  
addEdge(27, 10, 100, 200, 120, BUS);    // Vadodara-Ahmedabad  
addEdge(29, 15, 250, 500, 210, BUS);    // Amritsar-Chandigarh  
addEdge(31, 32, 150, 300, 120, BUS);    // Imphal-Shillong  
addEdge(33, 34, 700, 1500, 600, BUS);   // Aizawl-Panaji  
addEdge(2, 5, 1700, 3500, 150, FLIGHT);  // Kolkata-Bangalore  
addEdge(3, 8, 1800, 4000, 180, FLIGHT);  // Chennai-Lucknow  
addEdge(6, 21, 2200, 4500, 150, FLIGHT); // Jaipur-Thiruvananthapuram  
addEdge(9, 19, 1500, 3000, 120, FLIGHT); // Dehradun-Guwahati  
addEdge(12, 17, 500, 1200, 90, FLIGHT);  // Patna-Ranchi  
addEdge(18, 26, 600, 1500, 90, FLIGHT);  // Raipur-Visakhapatnam  
addEdge(22, 5, 400, 1000, 60, FLIGHT);   // Kochi-Bangalore  
addEdge(25, 4, 300, 800, 60, FLIGHT);    // Vijayawada-Hyderabad  
addEdge(30, 19, 350, 900, 60, FLIGHT);   // Agartala-Guwahati  
addEdge(34, 3, 800, 2000, 120, FLIGHT); // Panaji-Chennai  
// Delhi-Mumbai alternatives  
addEdge(0, 1, 1400, 1200, 960, TRAIN);  // Train (longer but cheaper)  
addEdge(0, 1, 1400, 2500, 720, BUS);    // Bus (mid-range)  

// Bangalore-Chennai alternatives  
addEdge(5, 3, 350, 800, 300, TRAIN);    // Train (cheapest)  
addEdge(5, 3, 350, 1500, 240, BUS);     // Bus (faster than train)  

// Kolkata-Guwahati alternatives  
addEdge(2, 19, 1020, 1200, 840, BUS);   // Bus (cheaper than train)  
addEdge(2, 19, 1020, 2500, 180, FLIGHT); // Flight (fastest)  

// Hyderabad-Bangalore alternatives  
addEdge(4, 5, 570, 900, 420, TRAIN);    // Train  
addEdge(4, 5, 570, 1200, 360, BUS);     // Bus  
addEdge(7, 27, 250, 450, 180, TRAIN);   // Surat-Vadodara (Express)
addEdge(10, 28, 1100, 1800, 720, TRAIN); // Ahmedabad-Jammu (Rajdhani)
addEdge(13, 17, 500, 850, 360, TRAIN);   // Bhopal-Ranchi (Intercity)
addEdge(16, 25, 650, 1100, 420, TRAIN); // Nagpur-Vijayawada (Superfast)
addEdge(20, 24, 1200, 2000, 780, TRAIN); // Bhubaneswar-Coimbatore (Shatabdi)
addEdge(22, 34, 800, 1500, 600, TRAIN); // Kochi-Panaji (Special)
addEdge(26, 30, 1400, 2200, 840, TRAIN); // Visakhapatnam-Agartala (Duronto)
addEdge(9, 29, 500, 800, 420, BUS);     // Dehradun-Amritsar (Volvo)
addEdge(11, 23, 1000, 1600, 660, BUS);  // Pune-Madurai (Sleeper)
addEdge(14, 18, 350, 600, 240, BUS);    // Indore-Raipur (AC)
addEdge(19, 33, 400, 700, 300, BUS);    // Guwahati-Aizawl (Hill Bus)
addEdge(21, 31, 1200, 2000, 720, BUS);  // Thiruvananthapuram-Imphal (Deluxe)
addEdge(24, 32, 1500, 2500, 900, BUS);  // Coimbatore-Shillong (Luxury)
addEdge(6, 22, 1800, 4000, 150, FLIGHT); // Jaipur-Kochi (Direct)
addEdge(8, 26, 1200, 3000, 120, FLIGHT); // Lucknow-Visakhapatnam (Non-stop)
addEdge(12, 30, 900, 2500, 90, FLIGHT);  // Patna-Agartala (Connecting)
addEdge(15, 23, 2200, 4500, 180, FLIGHT); // Chandigarh-Madurai (Via Delhi)
addEdge(18, 21, 1400, 3200, 150, FLIGHT); // Raipur-Thiruvananthapuram
addEdge(27, 33, 1600, 3500, 180, FLIGHT); // Vadodara-Aizawl (Premium)
// Mumbai-Kolkata alternatives
addEdge(1, 2, 2000, 3500, 1440, TRAIN); // Howrah Mail
addEdge(1, 2, 2000, 1800, 960, BUS);    // Luxury AC Bus
addEdge(1, 2, 1700, 4500, 150, FLIGHT); // Direct Flight

// Bangalore-Hyderabad alternatives
addEdge(5, 4, 570, 1200, 480, TRAIN);   // Shatabdi Express
addEdge(5, 4, 570, 900, 360, BUS);      // Overnight Bus
addEdge(5, 4, 570, 2500, 70, FLIGHT);   // Quick Flight

// Delhi-Chennai multi-mode
addEdge(0, 3, 2200, 1800, 1260, TRAIN); // Grand Trunk Express
addEdge(0, 3, 2200, 2500, 900, BUS);    // Super Deluxe Bus
addEdge(0, 3, 2200, 4500, 180, FLIGHT); // Non-stop Flight
// Mumbai-Kolkata alternatives
addEdge(1, 2, 2000, 3500, 1440, TRAIN); // Howrah Mail
addEdge(1, 2, 2000, 1800, 960, BUS);    // Luxury AC Bus
addEdge(1, 2, 1700, 4500, 150, FLIGHT); // Direct Flight

// Bangalore-Hyderabad alternatives
addEdge(5, 4, 570, 1200, 480, TRAIN);   // Shatabdi Express
addEdge(5, 4, 570, 900, 360, BUS);      // Overnight Bus
addEdge(5, 4, 570, 2500, 70, FLIGHT);   // Quick Flight

// Delhi-Chennai multi-mode
addEdge(0, 3, 2200, 1800, 1260, TRAIN); // Grand Trunk Express
addEdge(0, 3, 2200, 2500, 900, BUS);    // Super Deluxe Bus
addEdge(0, 3, 2200, 4500, 180, FLIGHT); // Non-stop Flight
    // Flight connections
    addEdge(0, 1, 1400, 3500, 120, FLIGHT); // Delhi-Mumbai
    addEdge(0, 2, 1500, 4000, 150, FLIGHT); // Delhi-Kolkata
    addEdge(0, 3, 2200, 4500, 180, FLIGHT); // Delhi-Chennai
    addEdge(1, 3, 1350, 3800, 135, FLIGHT); // Mumbai-Chennai
    addEdge(2, 3, 1650, 4200, 150, FLIGHT); // Kolkata-Chennai
    addEdge(4, 5, 570, 2500, 70, FLIGHT);   // Hyderabad-Bangalore
    addEdge(3, 4, 630, 1000, 480, FLIGHT);  // Chennai-Hyderabad
    addEdge(5, 21, 730, 1500, 720, FLIGHT); // Bangalore-Thiruvananthapuram
    addEdge(30, 31, 310, 600, 300, FLIGHT); // Agartala-Imphal
    addEdge(31, 33, 270, 500, 300, FLIGHT); // Imphal-Aizawl
    addEdge(34, 1, 590, 1200, 360, FLIGHT); // Panaji-Mumbai
    addEdge(7, 24, 1400, 2200, 900, TRAIN);   // Surat-Coimbatore (Weekly Express)
addEdge(10, 20, 1600, 2500, 1020, TRAIN); // Ahmedabad-Bhubaneswar (Gujarat Mail)
addEdge(12, 22, 1800, 2800, 1140, TRAIN);  // Patna-Kochi (Bihar-Kerala Special)
addEdge(16, 26, 800, 1300, 540, TRAIN);    // Nagpur-Visakhapatnam (Godavari Express)
addEdge(19, 25, 1200, 1900, 780, TRAIN);   // Guwahati-Vijayawada (NE-South Connect)
addEdge(23, 34, 1000, 1700, 660, TRAIN);   // Madurai-Panaji (Coastal Special)
addEdge(9, 28, 600, 1000, 480, BUS);      // Dehradun-Jammu (Himalayan Express)
addEdge(11, 17, 1200, 2000, 840, BUS);    // Pune-Ranchi (Plateau Connector)
addEdge(14, 30, 1800, 3000, 1200, BUS);   // Indore-Agartala (Trans-India AC)
addEdge(18, 21, 1500, 2500, 960, BUS);    // Raipur-Thiruvananthapuram (Monsoon Special)
addEdge(27, 31, 2200, 3500, 1320, BUS);   // Vadodara-Imphal (Golden Quadrilateral)
addEdge(29, 33, 500, 900, 360, BUS);      // Amritsar-Aizawl (Pilgrim Special)
addEdge(6, 20, 1200, 3500, 120, FLIGHT);  // Jaipur-Bhubaneswar (Udan Scheme)
addEdge(8, 16, 800, 2800, 90, FLIGHT);    // Lucknow-Nagpur (Red Eye Flight)
addEdge(13, 22, 1100, 3200, 150, FLIGHT); // Bhopal-Kochi (Monsoon Discount)
addEdge(15, 23, 2200, 4500, 180, FLIGHT); // Chandigarh-Madurai (Heritage Tour)
addEdge(17, 34, 1600, 3800, 150, FLIGHT); // Ranchi-Panaji (Weekend Getaway)
addEdge(24, 32, 1400, 3000, 120, FLIGHT); // Coimbatore-Shillong (Tea Lovers Special)
// Chennai-Shillong options
addEdge(3, 32, 2200, 1800, 1260, TRAIN); // Vivek Express (Longest Route)
addEdge(3, 32, 2200, 3500, 900, BUS);    // Cross-Country AC Sleeper
addEdge(3, 32, 1800, 5000, 180, FLIGHT); // Connecting Flight

// Mumbai-Imphal alternatives
addEdge(1, 31, 2200, 2500, 1140, TRAIN); // Northeast Rajdhani
addEdge(1, 31, 2200, 4000, 960, BUS);    // Luxury Sleeper
addEdge(1, 31, 1800, 6000, 210, FLIGHT); // Direct Flight

// Bangalore-Aizawl choices
addEdge(5, 33, 2000, 3000, 1200, TRAIN); // Southern Zonal Express
addEdge(5, 33, 2000, 4500, 840, BUS);    // Hill Country Deluxe
addEdge(5, 33, 1500, 5500, 180, FLIGHT); // Quick Connection
    
    // Multiple options
    addEdge(0, 4, 1550, 2500, 1020, TRAIN); // Delhi-Hyderabad (Train)
    addEdge(0, 4, 1550, 4000, 120, FLIGHT);  // Delhi-Hyderabad (Flight)
    addEdge(5, 8, 1500, 1800, 960, BUS);     // Bangalore-Lucknow (Bus)
    addEdge(5, 8, 1500, 5000, 180, FLIGHT);  // Bangalore-Lucknow (Flight)
    addEdge(3, 9, 2400, 4200, 180, FLIGHT);  // Chennai-Dehradun
    addEdge(6, 8, 480, 700, 300, TRAIN);     // Jaipur-Lucknow
    addEdge(7, 10, 320, 600, 240, TRAIN);    // Surat-Ahmedabad
    addEdge(11, 4, 610, 1100, 300, TRAIN);   // Pune-Hyderabad
    addEdge(13, 14, 260, 400, 180, BUS);     // Bhopal-Indore
    addEdge(12, 8, 950, 1600, 600, TRAIN);   // Patna-Lucknow
    addEdge(17, 20, 720, 1200, 450, TRAIN);  // Ranchi-Bhubaneswar
    addEdge(18, 13, 520, 900, 360, BUS);     // Raipur-Bhopal
    addEdge(19, 12, 1100, 1900, 660, TRAIN); // Guwahati-Patna
    addEdge(22, 23, 400, 700, 300, BUS);     // Trichy-Madurai
    addEdge(27, 28, 190, 300, 150, BUS);     // Vadodara-Jammu
    addEdge(26, 2, 870, 1700, 420, TRAIN);   // Visakhapatnam-Kolkata
    addEdge(30, 33, 520, 1000, 400, FLIGHT); // Agartala-Aizawl
    addEdge(1, 21, 980, 2400, 90, FLIGHT);   // Mumbai-Thiruvananthapuram
    addEdge(15, 6, 510, 800, 300, BUS);      // Chandigarh-Jaipur
    addEdge(31, 34, 830, 1600, 480, FLIGHT); // Imphal-Panaji
    addEdge(24, 22, 320, 600, 240, TRAIN);   // Coimbatore-Trichy
    addEdge(20, 17, 740, 1200, 420, TRAIN);  // Bhubaneswar-Ranchi
    addEdge(5, 13, 380, 800, 330, TRAIN);    // Bangalore-Bhopal
    addEdge(3, 22, 450, 700, 360, TRAIN);    // Chennai-Trichy
    addEdge(2, 6, 980, 1800, 720, TRAIN);    // Kolkata-Jaipur
    addEdge(16, 4, 700, 1400, 480, TRAIN);   // Nagpur-Hyderabad
    addEdge(24, 21, 420, 800, 360, BUS);     // Coimbatore-Thiruvananthapuram
    addEdge(7, 27, 180, 350, 150, BUS);      // Surat-Vadodara
    addEdge(8, 9, 570, 800, 300, TRAIN);     // Lucknow-Dehradun
    addEdge(26, 17, 560, 1000, 420, TRAIN);  // Visakhapatnam-Ranchi
    addEdge(10, 1, 490, 900, 240, TRAIN);    // Ahmedabad-Mumbai
    addEdge(14, 11, 620, 1100, 390, BUS);    // Indore-Pune
    addEdge(30, 32, 450, 800, 360, TRAIN);   // Agartala-Shillong
    addEdge(29, 0, 450, 700, 330, TRAIN);    // Amritsar-Delhi
    addEdge(22, 5, 600, 1000, 420, FLIGHT);  // Trichy-Bangalore
    addEdge(19, 33, 750, 1500, 480, FLIGHT);// Guwahati-Aizawl
    addEdge(12, 2, 710, 1300, 360, TRAIN);   // Patna-Kolkata
    addEdge(34, 5, 600, 1400, 300, FLIGHT);  // Panaji-Bangalore
    addEdge(25, 22, 450, 700, 300, TRAIN);   // Vijayawada-Trichy
    addEdge(15, 27, 510, 900, 330, BUS);     // Chandigarh-Vadodara
    addEdge(6, 5, 1900, 2200, 120, FLIGHT);  // Jaipur-Bangalore
    addEdge(13, 6, 510, 800, 300, TRAIN);    // Bhopal-Jaipur
    addEdge(31, 30, 250, 500, 210, BUS);     // Imphal-Agartala
    addEdge(20, 19, 890, 1500, 480, TRAIN);  // Bhubaneswar-Guwahati
    // Additional edges for more city connections
addEdge(0, 1, 1400, 1200, 960, TRAIN);  // Delhi-Mumbai (Train)
addEdge(0, 2, 1500, 4000, 150, FLIGHT); // Delhi-Kolkata (Flight)
addEdge(1, 3, 1350, 3800, 135, FLIGHT); // Mumbai-Chennai (Flight)
addEdge(2, 3, 1650, 4200, 150, FLIGHT); // Kolkata-Chennai (Flight)
addEdge(4, 5, 570, 2500, 70, FLIGHT);   // Hyderabad-Bangalore (Flight)
addEdge(3, 4, 630, 1000, 480, FLIGHT);  // Chennai-Hyderabad (Flight)
addEdge(5, 21, 730, 1500, 720, FLIGHT); // Bangalore-Thiruvananthapuram (Flight)
addEdge(30, 31, 310, 600, 300, FLIGHT); // Agartala-Imphal (Flight)
addEdge(31, 33, 270, 500, 300, FLIGHT); // Imphal-Aizawl (Flight)
addEdge(34, 1, 590, 1200, 360, FLIGHT); // Panaji-Mumbai (Flight)
addEdge(7, 24, 1400, 2200, 900, TRAIN);   // Surat-Coimbatore (Weekly Express)
addEdge(10, 20, 1600, 2500, 1020, TRAIN); // Ahmedabad-Bhubaneswar (Gujarat Mail)
addEdge(12, 22, 1800, 2800, 1140, TRAIN);  // Patna-Kochi (Bihar-Kerala Special)
addEdge(16, 26, 800, 1300, 540, TRAIN);    // Nagpur-Visakhapatnam (Godavari Express)
addEdge(19, 25, 1200, 1900, 780, TRAIN);   // Guwahati-Vijayawada (NE-South Connect)
addEdge(23, 34, 1000, 1700, 660, TRAIN);   // Madurai-Panaji (Coastal Special)
addEdge(9, 28, 600, 1000, 480, BUS);      // Dehradun-Jammu (Himalayan Express)
addEdge(11, 17, 1200, 2000, 840, BUS);    // Pune-Ranchi (Plateau Connector)
addEdge(14, 30, 1800, 3000, 1200, BUS);   // Indore-Agartala (Trans-India AC)
addEdge(18, 21, 1500, 2500, 960, BUS);    // Raipur-Thiruvananthapuram (Monsoon Special)
addEdge(27, 31, 2200, 3500, 1320, BUS);   // Vadodara-Imphal (Golden Quadrilateral)
addEdge(29, 33, 500, 900, 360, BUS);      // Amritsar-Aizawl (Pilgrim Special)
addEdge(6, 20, 1200, 3500, 120, FLIGHT);  // Jaipur-Bhubaneswar (Udan Scheme)
addEdge(8, 16, 800, 2800, 90, FLIGHT);    // Lucknow-Nagpur (Red Eye Flight)
addEdge(13, 22, 1100, 3200, 150, FLIGHT); // Bhopal-Kochi (Monsoon Discount)
addEdge(15, 23, 2200, 4500, 180, FLIGHT); // Chandigarh-Madurai (Heritage Tour)
addEdge(17, 34, 1600, 3800, 150, FLIGHT); // Ranchi-Panaji (Weekend Getaway)
addEdge(24, 32, 1400, 3000, 120, FLIGHT); // Coimbatore-Shillong (Tea Lovers Special)
addEdge(3, 32, 2200, 1800, 1260, TRAIN); // Chennai-Shillong (Vivek Express)
addEdge(1, 31, 2200, 2500, 1140, TRAIN); // Mumbai-Imphal (Northeast Rajdhani)
addEdge(4, 10, 800, 1500, 600, TRAIN); // Hyderabad-Ahmedabad
// Additional edges for more city connections
addEdge(0, 1, 1400, 1200, 960, TRAIN);  // Delhi-Mumbai (Train)
addEdge(0, 2, 1500, 4000, 150, FLIGHT); // Delhi-Kolkata (Flight)
addEdge(1, 3, 1350, 3800, 135, FLIGHT); // Mumbai-Chennai (Flight)
addEdge(2, 3, 1650, 4200, 150, FLIGHT); // Kolkata-Chennai (Flight)
addEdge(4, 5, 570, 2500, 70, FLIGHT);   // Hyderabad-Bangalore (Flight)
addEdge(3, 4, 630, 1000, 480, FLIGHT);  // Chennai-Hyderabad (Flight)
addEdge(5, 21, 730, 1500, 720, FLIGHT); // Bangalore-Thiruvananthapuram (Flight)
addEdge(30, 31, 310, 600, 300, FLIGHT); // Agartala-Imphal (Flight)
addEdge(31, 33, 270, 500, 300, FLIGHT); // Imphal-Aizawl (Flight)
addEdge(34, 1, 590, 1200, 360, FLIGHT); // Panaji-Mumbai (Flight)
addEdge(7, 24, 1400, 2200, 900, TRAIN);   // Surat-Coimbatore (Weekly Express)
addEdge(10, 20, 1600, 2500, 1020, TRAIN); // Ahmedabad-Bhubaneswar (Gujarat Mail)
addEdge(12, 22, 1800, 2800, 1140, TRAIN);  // Patna-Kochi (Bihar-Kerala Special)
addEdge(16, 26, 800, 1300, 540, TRAIN);    // Nagpur-Visakhapatnam (Godavari Express)
addEdge(19, 25, 1200, 1900, 780, TRAIN);   // Guwahati-Vijayawada (NE-South Connect)
addEdge(23, 34, 1000, 1700, 660, TRAIN);   // Madurai-Panaji (Coastal Special)
addEdge(9, 28, 600, 1000, 480, BUS);      // Dehradun-Jammu (Himalayan Express)
addEdge(11, 17, 1200, 2000, 840, BUS);    // Pune-Ranchi (Plateau Connector)
addEdge(14, 30, 1800, 3000, 1200, BUS);   // Indore-Agartala (Trans-India AC)
addEdge(18, 21, 1500, 2500, 960, BUS);    // Raipur-Thiruvananthapuram (Monsoon Special)
addEdge(27, 31, 2200, 3500, 1320, BUS);   // Vadodara-Imphal (Golden Quadrilateral)
addEdge(29, 33, 500, 900, 360, BUS);      // Amritsar-Aizawl (Pilgrim Special)
addEdge(6, 20, 1200, 3500, 120, FLIGHT);  // Jaipur-Bhubaneswar (Udan Scheme)
addEdge(8, 16, 800, 2800, 90, FLIGHT);    // Lucknow-Nagpur (Red Eye Flight)
addEdge(13, 22, 1100, 3200, 150, FLIGHT); // Bhopal-Kochi (Monsoon Discount)
addEdge(15, 23, 2200, 4500, 180, FLIGHT); // Chandigarh-Madurai (Heritage Tour)
addEdge(17, 34, 1600, 3800, 150, FLIGHT); // Ranchi-Panaji (Weekend Getaway)
addEdge(24, 32, 1400, 3000, 120, FLIGHT); // Coimbatore-Shillong (Tea Lovers Special)
addEdge(3, 32, 2200, 1800, 1260, TRAIN); // Chennai-Shillong (Vivek Express)
addEdge(1, 31, 2200, 2500, 1140, TRAIN); // Mumbai-Imphal (Northeast Rajdhani)
addEdge(0, 4, 1550, 2500, 1020, TRAIN);  // Delhi-Hyderabad
addEdge(0, 5, 1500, 3000, 1200, FLIGHT); // Delhi-Bangalore
addEdge(1, 2, 2000, 3500, 1440, TRAIN);  // Mumbai-Kolkata
addEdge(1, 4, 700, 1500, 600, BUS);      // Mumbai-Hyderabad
addEdge(2, 3, 1650, 4200, 150, FLIGHT);  // Kolkata-Chennai
addEdge(3, 5, 350, 800, 300, TRAIN);     // Chennai-Bangalore
addEdge(4, 6, 600, 1200, 480, BUS);      // Hyderabad-Jaipur
addEdge(5, 7, 800, 1500, 600, TRAIN);    // Bangalore-Mumbai
addEdge(6, 8, 700, 1300, 360, BUS);      // Jaipur-Lucknow
addEdge(7, 9, 500, 1000, 240, TRAIN);    // Mumbai-Dehradun
addEdge(8, 10, 600, 1200, 300, FLIGHT);  // Lucknow-Ahmedabad
addEdge(9, 11, 400, 800, 180, BUS);      // Dehradun-Pune
addEdge(10, 12, 800, 1500, 600, TRAIN);  // Ahmedabad-Patna
addEdge(11, 13, 300, 600, 240, BUS);     // Pune-Bhopal
addEdge(12, 14, 500, 1000, 300, TRAIN);  // Patna-Indore
addEdge(13, 15, 400, 800, 180, BUS);     // Bhopal-Chandigarh
addEdge(14, 16, 600, 1200, 480, TRAIN);  // Indore-Nagpur
addEdge(15, 17, 700, 1500, 600, FLIGHT); // Chandigarh-Ranchi
addEdge(16, 18, 800, 1600, 720, TRAIN);  // Nagpur-Raipur
addEdge(17, 19, 900, 1800, 840, BUS);     // Ranchi-Guwahati
addEdge(18, 20, 1000, 2000, 960, TRAIN); // Raipur-Bhubaneswar
addEdge(19, 21, 1100, 2200, 1080, FLIGHT); // Guwahati-Thiruvananthapuram
addEdge(20, 22, 1200, 2400, 1200, BUS);  // Bhubaneswar-Kochi
addEdge(21, 23, 1300, 2600, 1320, TRAIN); // Thiruvananthapuram-Madurai
addEdge(22, 24, 1400, 2800, 1440, FLIGHT); // Kochi-Coimbatore
addEdge(23, 25, 1500, 3000, 1560, BUS);  // Madurai-Vijayawada
addEdge(24, 26, 1600, 3200, 1680, TRAIN); // Coimbatore-Visakhapatnam
addEdge(25, 27, 1700, 3400, 1800, FLIGHT); // Vijayawada-Jaipur
addEdge(26, 28, 1800, 3600, 1920, BUS);  // Visakhapatnam-Ahmedabad
addEdge(27, 29, 1900, 3800, 2040, TRAIN); // Jaipur-Mumbai
addEdge(28, 30, 2000, 4000, 2160, FLIGHT); // Ahmedabad-Delhi
addEdge(29, 31, 2100, 4200, 2280, BUS);  // Mumbai-Agartala
addEdge(30, 32, 2200, 4400, 2400, TRAIN); // Delhi-Imphal
addEdge(31, 33, 2300, 4600, 2520, FLIGHT); // Agartala-Aizawl
addEdge(32, 34, 2400, 4800, 2640, BUS);  // Imphal-Panaji
addEdge(33, 0, 2500, 5000, 2760, TRAIN); // Aizawl-Delhi
addEdge(34, 1, 2600, 5200, 2880, FLIGHT); // Panaji-Mumbai
addEdge(0, 2, 2700, 5400, 3000, BUS);    // Delhi-Kolkata
addEdge(1, 3, 2800, 5600, 3120, TRAIN);  // Mumbai-Chennai
addEdge(2, 4, 2900, 5800, 3240, FLIGHT); // Kolkata-Hyderabad
addEdge(3, 5, 3000, 6000, 3360, BUS);    // Chennai-Bangalore

}

void printWelcomeMessage() {
    printf("\n" BOLD BLUE "       TRAVEL PLANNER APPLICATION" RESET);
    printf("\n\n" BOLD GREEN "Key Features:" RESET);
    printf("\n- " YELLOW "Find routes by multiple criteria" RESET);
    printf("\n- " YELLOW "Search within specific budget" RESET);
    printf("\n- " YELLOW "Multiple transportation options" RESET);
    printf("\n- " YELLOW "Clear route details with costs" RESET);
}

int main() {
    setupGraph();
    printWelcomeMessage();

    int choice;
    char start[50], end[50];
    int budget;

    do {
        printf("\n\n" BOLD MAGENTA "Main Menu:" RESET "\n");
        printf(BOLD "1." RESET " " CYAN "Find optimal route by criteria\n" RESET);
        printf(BOLD "2." RESET " " CYAN "Find routes within budget\n" RESET);
        printf(BOLD "3." RESET " " CYAN "View available cities\n" RESET);
        printf(BOLD "4." RESET " " CYAN "Exit\n" RESET);
        printf(BOLD YELLOW "Enter your choice: " RESET);
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: {
                printf(BOLD YELLOW "\nEnter starting city: " RESET);
                fgets(start, sizeof(start), stdin);
                start[strcspn(start, "\n")] = 0;

                printf(BOLD YELLOW "Enter destination city: " RESET);
                fgets(end, sizeof(end), stdin);
                end[strcspn(end, "\n")] = 0;

                int src = getCityIndex(start);
                int dest = getCityIndex(end);

                if (src == -1 || dest == -1) {
                    printf(RED "Invalid city name! Please try again.\n" RESET);
                    break;
                }

                printf(BOLD YELLOW "\nSelect up to %d criteria (enter numbers separated by spaces):\n" RESET, MAX_CRITERIA);
                printf(BOLD "1." RESET " Distance (km)\n");
                printf(BOLD "2." RESET " Cost (Rs)\n");
                printf(BOLD "3." RESET " Time (minutes)\n");
                printf(BOLD YELLOW "Enter your choices: " RESET);

                char input[50];
                fgets(input, sizeof(input), stdin);

                int criteria[MAX_CRITERIA] = {0};
                int criteriaCount = 0;
                char *token = strtok(input, " ");
                while (token && criteriaCount < MAX_CRITERIA) {
                    int crit = atoi(token) - 1;
                    if (crit >= 0 && crit <= 2) {
                        criteria[criteriaCount++] = crit;
                    }
                    token = strtok(NULL, " ");
                }

                if (criteriaCount == 0) {
                    printf(RED "Invalid selection. Please choose at least one criteria.\n" RESET);
                    break;
                }

                printf(GREEN "\nSearching for optimal route from %s to %s...\n" RESET, cities[src], cities[dest]);
                findOptimalPath(src, dest, criteria, criteriaCount);
                break;
            }

            case 2: {
                printf(BOLD YELLOW "\nEnter starting city: " RESET);
                fgets(start, sizeof(start), stdin);
                start[strcspn(start, "\n")] = 0;

                printf(BOLD YELLOW "Enter destination city: " RESET);
                fgets(end, sizeof(end), stdin);
                end[strcspn(end, "\n")] = 0;

                printf(BOLD YELLOW "Enter your maximum budget (Rs.): " RESET);
                scanf("%d", &budget);
                getchar();

                int src = getCityIndex(start);
                int dest = getCityIndex(end);

                if (src == -1 || dest == -1) {
                    printf(RED "Invalid city name! Please try again.\n" RESET);
                    break;
                }

                if (budget <= 0) {
                    printf(RED "Budget must be positive amount\n" RESET);
                    break;
                }

                printf(GREEN "\nSearching for routes under  Rs.%d...\n" RESET, budget);
                findRoutesWithinBudget(src, dest, budget);
                break;
            }

            case 3:
                viewCities();
                break;

            case 4:
                printf(GREEN "\nThank you for using Travel Planner!\n" RESET);
                break;

            default:
                printf(RED "Invalid choice. Please try again.\n" RESET);
        }
    } while (choice != 4);
   return 0;
}
