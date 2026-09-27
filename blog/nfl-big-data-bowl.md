
---
layout: post
title: "🏈 NFL Big Data Bowl 2026 — Player Trajectory Prediction"
date: 2025-11-11
categories: [AI, Sports Analytics, Trajectory Forecasting, NFL]
---

# 🏈 NFL Big Data Bowl 2026 — Player Movement Prediction

## 📘 Overview

The **2026 Big Data Bowl** challenges participants to predict **NFL player movement** during the frames **after the quarterback throws the ball** — the critical moment when receivers and defenders converge toward the ball landing point.

This competition aims to help the **NFL Next Gen Stats** team better understand how players move, interact, and position themselves while the ball is in flight.

> The model must predict each player's `x` and `y` coordinates for every frame between the **ball release** and **pass completion/incompletion**.

---

## 🎯 Objective

Given:
- Player tracking data **before the pass is thrown**, and  
- Metadata including the **targeted receiver** and **ball landing location**

Your task is to **predict player trajectories (x, y positions)** for each frame **after the ball is released** until the play ends.

---

## 🧩 Dataset Description

The dataset is split into **input** (pre-throw) and **output** (post-throw) tracking data.

### 📂 Files

#### `train/input_2023_w[01–18].csv`
Tracking data **before the pass**.

| Column | Description |
|---------|--------------|
| `game_id` | Unique game identifier |
| `play_id` | Play identifier (not unique across games) |
| `player_to_predict` | Whether this player’s trajectory will be scored |
| `nfl_id` | Unique player ID |
| `frame_id` | Frame number within play |
| `play_direction` | “Left” or “Right” (offensive direction) |
| `absolute_yardline_number` | Distance from end zone for possession team |
| `player_name` | Player full name |
| `player_height`, `player_weight`, `player_birth_date` | Biographical data |
| `player_position`, `player_side` | Position (WR, CB, QB, etc.) and team side (Offense / Defense) |
| `player_role` | Role in the play — *Defensive Coverage*, *Targeted Receiver*, *Passer*, or *Other Route Runner* |
| `x`, `y` | Player field position in yards |
| `s`, `a` | Speed (yards/s), Acceleration (yards/s²) |
| `o`, `dir` | Orientation and movement direction in degrees |
| `num_frames_output` | Number of frames to predict after the throw |
| `ball_land_x`, `ball_land_y` | Ball landing coordinates |

#### `train/output_2023_w[01–18].csv`
Tracking data **after the pass** — the **targets to predict**.

| Column | Description |
|---------|--------------|
| `game_id`, `play_id`, `nfl_id` | Same identifiers as input |
| `frame_id` | Frame number (1..num_frames_output) |
| `x`, `y` | True player coordinates — *TARGET VARIABLES* |

#### `test_input.csv` / `test.csv`
Mock test data provided for local testing.  
The real test data is served through the **Kaggle evaluation API** during the live forecasting phase.

---

## 📊 Evaluation

Submissions are scored using **Root Mean Squared Error (RMSE)**:

\[
RMSE = \sqrt{\frac{1}{N} \sum_{i=1}^{N} ((x_i - \hat{x}_i)^2 + (y_i - \hat{y}_i)^2)}
\]

Where:
- \( (x_i, y_i) \) = true player positions  
- \( (\hat{x}_i, \hat{y}_i) \) = predicted positions

You must output **predicted x, y** for every `(game_id, play_id, nfl_id, frame_id)` combination in the test set.

---

## 🕓 Timeline

### **Training Phase**
- 🏁 *Start:* September 25, 2025  
- 👥 *Team Merge Deadline:* November 26, 2025  
- 🚪 *Entry Deadline:* November 26, 2025  
- 📤 *Final Submission:* December 3, 2025  

### **Forecasting Phase**
- 🗓️ *December 4, 2025 – January 5, 2026*  
- Live leaderboard updates after each week’s games  
- 🏆 *Competition Ends:* January 6, 2026  

---

## ⚙️ Modeling Approach

A successful solution must learn realistic **player trajectories** under dynamic, multi-agent interactions.  
A solid pipeline includes:

### 1️⃣ Feature Engineering
- Player motion history: `(x, y, s, a, o, dir)`  
- Context: `play_direction`, `absolute_yardline_number`, `player_role`  
- Game state: `ball_land_x, ball_land_y`, targeted receiver flag  
- Team/role encoding: Offense vs Defense  

### 2️⃣ Model Architecture
- **Encoder:** temporal model (LSTM / Transformer) to process pre-throw frames  
- **Interaction Module:** Graph Neural Network to model offense-defense interactions  
- **Decoder:** predicts multi-step future `(x, y)` positions until `num_frames_output`

Example high-level structure:
```

[ Input sequence (pre-throw) ]
↓
Temporal Encoder (LSTM/Transformer)
↓
Player Interaction Graph
↓
Multi-Step Decoder → Predicted (x, y)

```

### 3️⃣ Baseline Idea
A simple physics-inspired baseline:
- Receivers → move linearly toward ball landing point  
- Defenders → move toward ball landing or targeted receiver  
- Others → continue current motion vector  

---

## 🧠 Key Insights

- Plays are sampled at **10 frames per second**.  
- Only “real” passes (not deflections or throwaways) are included.  
- Pre-throw context is rich — includes player roles and ball landing zone.  
- The **targeted receiver** and **ball landing location** are highly predictive cues.  
- Interaction modeling between offense and defense is crucial.

---

## 🧰 Expected Tools & Libraries

- **Python 3.10+**
- **Pandas / NumPy** for data prep  
- **PyTorch / TensorFlow** for model training  
- **PyTorch Geometric / DGL** for GNN-based interaction modeling  
- **scikit-learn** for baselines and evaluation  

---

## 📁 Example Submission Schema

| game_id | play_id | nfl_id | frame_id | x | y |
|----------|----------|--------|-----------|----|----|
| 2023120301 | 45 | 2557981 | 1 | 56.3 | 29.4 |
| 2023120301 | 45 | 2557981 | 2 | 57.2 | 28.9 |
| ... | ... | ... | ... | ... | ... |

Each row corresponds to **one player in one future frame**.

---

## 🏆 Conclusion

The **Big Data Bowl 2026 Prediction Competition** combines **sports analytics**, **trajectory forecasting**, and **multi-agent modeling** in a real-world context.  
The challenge pushes participants to blend **physics, ML, and game understanding** to simulate realistic player movements.

> "When the ball is in the air, anything can happen — touchdowns, interceptions, or brilliance in motion. Our job is to predict that motion."

---

![NFL Big Data Bowl 2026 Pipeline](/assets/images/nfl_big_data_bowl_2026_pipeline.png)

---

**Author:** Oleg Lihvoinen  
**Tags:** `AI`, `Sports Analytics`, `ML`, `Trajectory Forecasting`, `NFL Big Data Bowl`
```

---
