/**
 * Smart Energy Usage Monitor - Logic Engine (JavaScript Implementation)
 * This file implements the same advanced data structures as the C++ version:
 * - Hash Map (Object) for Device lookup
 * - Graph (Adjacency List) for room connections
 * - Queue for real-time readings
 * - Sliding Window for rolling average
 * - Priority Queue (Sorted) for top consumers
 */

class Device {
    constructor(id, name, powerRating, room) {
        this.id = id;
        this.name = name;
        this.powerRating = powerRating;
        this.room = room;
        this.status = false;
    }

    getCurrentUsage() {
        return this.status ? this.powerRating : 0;
    }
}

class EnergyMonitor {
    constructor(windowSize = 10, threshold = 3000) {
        this.devices = {}; // Hash Map
        this.graph = new Map(); // Adjacency List
        this.dataStream = []; // Queue
        this.slidingWindow = []; // Deque for Sliding Window
        this.windowSize = windowSize;
        this.threshold = threshold;
        this.peakUsage = 0;
        this.peakTime = 0;
        this.simTimer = null;
        this.currentTime = 0;
        
        // New Data Structures
        this.undoStack = []; // STACK
        this.alerts = []; // LINKED LIST (Simulated with Array for UI)
        this.fullHistory = []; // For Merge Sort analysis
    }

    addDevice(id, name, powerRating, room) {
        const device = new Device(id, name, powerRating, room);
        this.devices[id] = device;
        
        // Graph Logic
        if (!this.graph.has(room)) this.graph.set(room, []);
        this.graph.get(room).push(id);
        
        this.updateDeviceUI();
    }

    toggleDevice(id, isUndo = false) {
        if (this.devices[id]) {
            this.devices[id].status = !this.devices[id].status;
            if (!isUndo) this.undoStack.push(id); // Push to STACK
            this.updateDeviceUI();
            this.calculateCurrentStats();
        }
    }

    undo() {
        if (this.undoStack.length === 0) return;
        const lastId = this.undoStack.pop(); // POP from STACK
        this.toggleDevice(lastId, true);
    }


    // Process incoming queue of data
    processTick() {
        this.currentTime++;
        let totalUsage = 0;

        // Push current usage of all devices into the "Stream Queue"
        for (let id in this.devices) {
            const usage = this.devices[id].getCurrentUsage();
            this.dataStream.push({ id, usage, time: this.currentTime });
            totalUsage += usage;
        }

        // Sliding Window Logic
        this.slidingWindow.push(totalUsage);
        if (this.slidingWindow.length > this.windowSize) {
            this.slidingWindow.shift();
        }

        // Peak Usage Detection
        if (totalUsage > this.peakUsage) {
            this.peakUsage = totalUsage;
            this.peakTime = this.currentTime;
        }

        this.updateUI(totalUsage);
    }

    getTopConsumers() {
        // Use manual Bubble Sort logic for Data Structure demonstration
        let activeDevices = Object.values(this.devices).filter(d => d.status);
        
        // BUBBLE SORT IMPLEMENTATION
        for (let i = 0; i < activeDevices.length - 1; i++) {
            for (let j = 0; j < activeDevices.length - i - 1; j++) {
                if (activeDevices[j].powerRating < activeDevices[j + 1].powerRating) {
                    let temp = activeDevices[j];
                    activeDevices[j] = activeDevices[j + 1];
                    activeDevices[j + 1] = temp;
                }
            }
        }
        
        return activeDevices.slice(0, 3);
    }

    bubbleSortRanking() {
        alert("Re-calculating device priority ranks...");
        this.calculateCurrentStats();
    }

    mergeSortHistory() {
        if (this.fullHistory.length < 2) {
            alert("Not enough data for Merge Sort report yet!");
            return;
        }

        let data = [...this.fullHistory];
        
        // MERGE SORT IMPLEMENTATION
        const merge = (left, right) => {
            let result = [], i = 0, j = 0;
            while (i < left.length && j < right.length) {
                if (left[i].usage >= right[j].usage) result.push(left[i++]);
                else result.push(right[j++]);
            }
            return result.concat(left.slice(i)).concat(right.slice(j));
        };

        const sort = (arr) => {
            if (arr.length <= 1) return arr;
            let mid = Math.floor(arr.length / 2);
            return merge(sort(arr.slice(0, mid)), sort(arr.slice(mid)));
        };

        let sorted = sort(data).slice(0, 5);
        let report = "=== PEAK USAGE ANALYTICS ===\n\n";
        sorted.forEach((r, i) => {
            report += `${i+1}. ${r.usage}W at ${new Date(r.timestamp).toLocaleTimeString()}\n`;
        });
        alert(report);
    }

    getTrend() {
        if (this.slidingWindow.length < 2) return "STABLE";
        const half = Math.floor(this.slidingWindow.length / 2);
        const firstHalf = this.slidingWindow.slice(0, half);
        const secondHalf = this.slidingWindow.slice(half);
        
        const avg1 = firstHalf.reduce((a, b) => a + b, 0) / firstHalf.length;
        const avg2 = secondHalf.reduce((a, b) => a + b, 0) / secondHalf.length;

        if (avg2 > avg1 * 1.1) return "UPWARDS";
        if (avg2 < avg1 * 0.9) return "DOWNWARDS";
        return "STABLE";
    }

    // --- UI UPDATERS ---

    updateUI(totalUsage) {
        // Update Stats
        document.querySelector('.stat-card:nth-child(1) .value').innerText = totalUsage.toLocaleString();
        
        const avg = this.slidingWindow.reduce((a, b) => a + b, 0) / this.slidingWindow.length;
        const statusCard = document.querySelector('.alert-card');
        const statusText = statusCard.querySelector('.status-text');
        
        if (avg > this.threshold) {
            statusText.innerText = "WARNING";
            statusCard.style.borderColor = "#ff3d00";
            statusCard.classList.add('pulse');
        } else {
            statusText.innerText = "OPTIMAL";
            statusCard.style.borderColor = "var(--glass)";
            statusCard.classList.remove('pulse');
        }

        // Update Trend
        const trend = this.getTrend();
        document.querySelector('.trend-text').innerText = trend;

        // Update Alert Count (Simulated)
        const alertBadge = document.getElementById('alert-summary');
        if (avg > this.threshold) {
            alertBadge.querySelector('.count').innerText = "ALERT ACTIVE";
            alertBadge.classList.add('pulse');
        } else {
            alertBadge.querySelector('.count').innerText = "Optimal";
            alertBadge.classList.remove('pulse');
        }

        // Update Chart (Visualizing the Sliding Window)
        const bars = document.querySelectorAll('.mock-chart .bar');
        this.slidingWindow.forEach((val, i) => {
            if (bars[i]) {
                const height = (val / 5000) * 100; // Normalize to 5000W
                bars[i].style.height = `${Math.min(height, 100)}%`;
                if (val > this.threshold) bars[i].classList.add('warning');
                else bars[i].classList.remove('warning');
            }
        });

        // Update Top Consumers
        const top = this.getTopConsumers();
        const list = document.querySelector('.consumer-list');
        list.innerHTML = top.map((d, i) => `
            <li class="consumer-item">
                <div class="c-info">
                    <span class="c-rank">#${i+1}</span>
                    <span class="c-name">${d.name}</span>
                </div>
                <span class="c-usage">${d.powerRating}W</span>
            </li>
        `).join('');
    }

    updateDeviceUI() {
        const grid = document.querySelector('.device-grid');
        grid.innerHTML = Object.values(this.devices).map(d => `
            <div class="device-card ${d.status ? 'active' : ''}">
                <div class="d-icon">${this.getIcon(d.name)}</div>
                <div class="d-details">
                    <h3>${d.name}</h3>
                    <p>${d.room} • ID: ${d.id}</p>
                </div>
                <label class="switch">
                    <input type="checkbox" ${d.status ? 'checked' : ''} onchange="monitor.toggleDevice('${d.id}')">
                    <span class="slider round"></span>
                </label>
            </div>
        `).join('');
    }

    getIcon(name) {
        if (name.includes("AC")) return "";
        if (name.includes("TV")) return "";
        if (name.includes("Fridge") || name.includes("Refrigerator")) return "";
        if (name.includes("Heater")) return "";
        if (name.includes("Light")) return "";
        return "🔌";
    }

    calculateCurrentStats() {
        let total = 0;
        for (let id in this.devices) total += this.devices[id].getCurrentUsage();
        this.updateUI(total);
    }
}

// Initialize System
const monitor = new EnergyMonitor(10, 3000);

// Pre-load devices (Same as C++ project)
monitor.addDevice("D1", "AC Unit", 1500, "LivingRoom");
monitor.addDevice("D2", "Smart TV", 200, "LivingRoom");
monitor.addDevice("D3", "Refrigerator", 400, "Kitchen");
monitor.addDevice("D4", "Microwave", 1000, "Kitchen");
monitor.addDevice("D5", "Heater", 2000, "Bedroom");

// Setup Initialization via Double Click
const initBtn = document.getElementById('init-btn');
const initOverlay = document.getElementById('init-overlay');
const mainApp = document.getElementById('main-app');

initBtn.addEventListener('dblclick', () => {
    // 1. Fade out the overlay
    initOverlay.classList.add('fade-out');
    
    // 2. Show the main app after a small delay
    setTimeout(() => {
        mainApp.classList.remove('hidden');
        
        // 3. Start the real-time simulation logic
        startSimulation();
    }, 600);
});

function startSimulation() {
    setInterval(() => {
        monitor.processTick();
        
        // Update Clock
        const now = new Date();
        document.getElementById('clock').innerText = now.toLocaleTimeString();
    }, 1000);
}

// Form Handling Functions
function toggleForm() {
    const form = document.getElementById('add-device-form');
    form.classList.toggle('hidden');
}

function addNewDevice() {
    const id = document.getElementById('dev-id').value;
    const name = document.getElementById('dev-name').value;
    const power = parseFloat(document.getElementById('dev-power').value);
    const room = document.getElementById('dev-room').value;

    if (!id || !name || isNaN(power) || !room) {
        alert("Please fill all fields correctly!");
        return;
    }

    // Add to Logic Engine
    monitor.addDevice(id, name, power, room);
    
    // Clear Form & Close
    document.getElementById('dev-id').value = '';
    document.getElementById('dev-name').value = '';
    document.getElementById('dev-power').value = '';
    document.getElementById('dev-room').value = '';
    toggleForm();
}

// View Management (SPA Style)
function showView(viewId, el) {
    // 1. Hide all views
    document.querySelectorAll('.view-section').forEach(v => v.classList.add('hidden'));
    
    // 2. Show selected view
    document.getElementById(viewId).classList.remove('hidden');
    
    // 3. Update Sidebar UI
    document.querySelectorAll('.nav-item').forEach(nav => nav.classList.remove('active'));
    el.classList.add('active');
}

// Room Analysis (Graph Traversal Logic)
function runRoomAnalysis() {
    const room = document.getElementById('room-select').value;
    const resultsDiv = document.getElementById('graph-results');
    
    if (!room) {
        resultsDiv.innerHTML = '<p class="placeholder-text">Select a room to begin analysis...</p>';
        return;
    }

    // Simulate DFS/BFS traversal from Graph Manager
    const deviceIds = monitor.graph.get(room) || [];
    let totalPower = 0;
    
    let html = `<h3>Analysis for ${room}</h3><br>`;
    html += `<p style="color:var(--text-dim)">Scanning room network: "${room}"...</p><br>`;
    
    if (deviceIds.length === 0) {
        html += `<p>No devices connected to this room node.</p>`;
    } else {
        html += `<ul style="list-style:none; padding-left:1rem;">`;
        deviceIds.forEach(id => {
            const d = monitor.devices[id];
            totalPower += d.getCurrentUsage();
            html += `<li style="margin-bottom:0.8rem">🔹 <b>${d.name}</b> (${id}) - Rating: ${d.powerRating}W | Status: ${d.status ? 'ON' : 'OFF'}</li>`;
        });
        html += `</ul><br>`;
        html += `<div style="padding:1rem; background:var(--glass); border-radius:10px;">
                    <strong>Total Room Power Load: ${totalPower}W</strong>
                 </div>`;
    }
    
    resultsDiv.innerHTML = html;
}

// History Management (Queue Stream)
function updateHistoryUI(newReading) {
    const historyLog = document.getElementById('history-log');
    const d = monitor.devices[newReading.id];
    
    const row = document.createElement('tr');
    row.innerHTML = `
        <td>${new Date().toLocaleTimeString()}</td>
        <td>${d.name} (${newReading.id})</td>
        <td>${newReading.usage}W</td>
        <td style="color:${d.status ? 'var(--success)' : 'var(--text-dim)'}">${d.status ? 'ACTIVE' : 'OFF'}</td>
    `;
    
    // Insert at top of table
    historyLog.insertBefore(row, historyLog.firstChild);
    
    // Keep only last 20 entries
    if (historyLog.children.length > 20) {
        historyLog.removeChild(historyLog.lastChild);
    }
}

// Settings Update
function updateSettings() {
    const thresh = parseFloat(document.getElementById('set-threshold').value);
    const win = parseInt(document.getElementById('set-window').value);
    
    monitor.threshold = thresh;
    monitor.windowSize = win;
    alert("System Settings Updated!");
}

// BST Range Search Logic (Simulated)
function runTreeSearch() {
    const min = parseFloat(document.getElementById('min-p').value) || 0;
    const max = parseFloat(document.getElementById('max-p').value) || 99999;
    const resultsDiv = document.getElementById('tree-search-results');

    const matches = Object.values(monitor.devices).filter(d => 
        d.powerRating >= min && d.powerRating <= max
    ).sort((a, b) => a.powerRating - b.powerRating); // BST would return sorted

    if (matches.length > 0) {
        resultsDiv.classList.remove('hidden');
        resultsDiv.innerHTML = `<strong>BST Search Results (${matches.length} found):</strong><br><br>` + 
            matches.map(m => `<span class="tree-item">🌳 ${m.name} - ${m.powerRating} Watts</span>`).join('');
    } else {
        resultsDiv.classList.add('hidden');
    }
}


// Hook into existing monitor.processTick to update history
const originalTick = monitor.processTick;
monitor.processTick = function() {
    this.currentTime++;
    let totalUsage = 0;

    for (let id in this.devices) {
        const usage = this.devices[id].getCurrentUsage();
        const reading = { id, usage, time: this.currentTime };
        this.dataStream.push(reading);
        totalUsage += usage;
        
        // Log to history UI if usage is active
        if (usage > 0) {
            updateHistoryUI(reading);
            this.fullHistory.push({ usage, timestamp: Date.now() });
        }
    }

    this.slidingWindow.push(totalUsage);
    if (this.slidingWindow.length > this.windowSize) {
        this.slidingWindow.shift();
    }

    if (totalUsage > this.peakUsage) {
        this.peakUsage = totalUsage;
        this.peakTime = this.currentTime;
    }

    this.updateUI(totalUsage);
};



