// Initialize the map
var map = L.map('map').setView([0, 0], 2);

// Create a tile layer (you can choose a different tile provider if desired)
L.tileLayer('https://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png', {
  attribution: 'Map data &copy; <a href="https://www.openstreetmap.org/">OpenStreetMap</a> contributors',
  maxZoom: 18
}).addTo(map);

// Load the Sumo GeoJSON file
fetch('iot_project.geojson')
  .then(response => response.json())
  .then(data => {
    // Create a Leaflet GeoJSON layer and add it to the map
    L.geoJSON(data).addTo(map);
  });
