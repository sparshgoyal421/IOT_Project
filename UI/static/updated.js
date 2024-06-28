var ctx2 = document.getElementById('chart2').getContext('2d');
var chart2 = new Chart(ctx2, {
    type: 'bar',
    data: {
        labels: ['Signal 1', 'Signal 2', 'Signal 3'], // Set the labels for the bars
        datasets: [{
            label: 'Signal Status',
            data: [0, 0, 0], // Initial values for the bar heights
            backgroundColor: 'rgba(192, 75, 192, 0.5)',
            borderWidth: 1,
            borderColor: 'rgba(192, 75, 192, 1)',
        }]
    },
    options: {
        plugins:{
            title :{
                display:true,
                text: "Traffic Signal Status"
            }
        },
        scales: {
            x: {
                display: true,
                title: {
                    display: true,
                    text: 'Signal No.'
                }
            },
            y: {
                display: true,
                title: {
                    display: true,
                    text: 'Value'
                },
                suggestedMin: 0, // Set the minimum value for the y-axis
                suggestedMax: 1 // Set the maximum value for the y-axis
            }
        }
    }
});

function updateBar(chart, data) {
    chart.data.datasets[0].data = data; // Update the bar heights with new data
    chart.update();
}

var ctx3 = document.getElementById('chart3').getContext('2d');
var chart3 = new Chart(ctx3, {
    type: 'pie',
    data: {
        labels: ['Road 1', 'Road 2', 'Road 3'],
        datasets: [{
            label: 'Number of cars',
            data: [0, 0, 0], 
            backgroundColor: [
                'rgba(255, 99, 132, 0.5)',
                'rgba(54, 162, 235, 0.5)',
                'rgba(255, 206, 86, 0.5)',
                'rgba(75, 192, 192, 0.5)'
            ],
            borderColor: [
                'rgba(255, 99, 132, 1)',
                'rgba(54, 162, 235, 1)',
                'rgba(255, 206, 86, 1)',
                'rgba(75, 192, 192, 1)'
            ],
            borderWidth: 1
        }]
    },
    options: {
        plugins:{
            title :{
                display:true,
                text: "Junction Traffic distribution"
            }
        },
        responsive: true
    }
});

function updatePie(chart, data) {
    chart.data.datasets[0].data = data;
    chart.update();
}

function fetchData(endpoint) {
    fetch(endpoint)
        .then(response => response.json())
        .then(data => {
            var barData = data.slice(-3); // Last four values for the bar chart
            var pieData = data.slice(0, 3); // First four values for the pie chart

            updateBar(chart2, barData);
            updatePie(chart3, pieData);

            setTimeout(() => fetchData(endpoint), 1000);
        });
}
fetchData("/dataD")