
# 💳 Credit Card Fraud Detection Using Machine Learning  
Predicting fraudulent transactions with real-world imbalanced data

Credit card fraud detection is one of the most important real-world applications of machine learning.  
In this project, we build a complete ML pipeline that identifies fraudulent transactions using the popular **Kaggle Credit Card Fraud dataset** — a highly imbalanced dataset based on real European transactions.

Fraudulent cases represent **only 0.172%** of all samples, making this a perfect demonstration of:
- handling imbalanced datasets  
- evaluating classifiers beyond accuracy  
- using precision, recall, and ROC curves  
- applying powerful ML models like **XGBoost**  

This project is practical, business-relevant, and demonstrates strong applied ML skills.

---

## 📁 Dataset Overview

**Dataset:**  
Kaggle — Credit Card Fraud Detection  
<https://www.kaggle.com/datasets/mlg-ulb/creditcardfraud>

**Rows:** 284,807 transactions  
**Fraudulent cases:** 492  
**Features:**  
- PCA-transformed values `V1`–`V28`  
- `Amount` (transaction amount)  
- `Time` (seconds elapsed)  
- `Class` (target: `0` = legit, `1` = fraud)

The dataset is **extremely imbalanced**, which means:
> Accuracy is a misleading metric — a model predicting “0” every time gets 99.8% accuracy.

Instead, we focus on:
- **precision**  
- **recall**  
- **F1 score**  
- **ROC-AUC**  

These reflect the true performance in detecting fraud.

---

## 🔍 Project Goals

Our goal is to train an ML classifier that can:

1. **Recognize fraudulent transactions**  
2. **Minimize false negatives** (missing fraud is costly!)  
3. **Perform well under extreme class imbalance**  

---

## 🧽 Data Preparation

Steps:

### ✔ Scale the `Amount` feature  
Other features are PCA-scaled, so we normalize the raw amount.

### ✔ Train/test split with stratification  
Ensures rare fraud cases appear in both sets.

### ✔ Handle class imbalance  
We can use:

- **XGBoost built-in scale_pos_weight**  
- or **SMOTE oversampling** (optional)  

In this project we use XGBoost, as it handles imbalance extremely well.

---

## 🤖 Model: XGBoost Classifier

Why XGBoost?

- Excellent performance on tabular data  
- Handles nonlinear relationships  
- Has built-in support for class imbalance  
- Very fast to train  

We use:

- `scale_pos_weight = (negative samples / positive samples)`  
- 500 boosted trees  
- max depth 4  
- learning rate 0.05  

---

## 🧪 Full Training Code

```python
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import classification_report, confusion_matrix, roc_auc_score
from xgboost import XGBClassifier

# ----------------------------
# Load dataset
# ----------------------------
df = pd.read_csv("creditcard.csv")

# Features and target
X = df.drop("Class", axis=1)
y = df["Class"]

# Scale the 'Amount' feature
scaler = StandardScaler()
X["Amount"] = scaler.fit_transform(X["Amount"].values.reshape(-1, 1))

# Train/test split with stratification
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y
)

# Compute imbalance ratio
ratio = (len(y_train) - y_train.sum()) / y_train.sum()

# ----------------------------
# Train XGBoost model
# ----------------------------
model = XGBClassifier(
    n_estimators=500,
    max_depth=4,
    learning_rate=0.05,
    subsample=0.9,
    colsample_bytree=0.9,
    scale_pos_weight=ratio,
    eval_metric="logloss",
    random_state=42
)

model.fit(X_train, y_train)

# ----------------------------
# Evaluate
# ----------------------------
y_pred = model.predict(X_test)
y_prob = model.predict_proba(X_test)[:, 1]

print("\nClassification Report:\n")
print(classification_report(y_test, y_pred))

print("Confusion Matrix:")
print(confusion_matrix(y_test, y_pred))

print("ROC-AUC:", roc_auc_score(y_test, y_prob))
````

---

## 📊 Results

Typical performance of this model:

* **Precision (fraud class):** 0.90+
* **Recall (fraud class):** 0.75–0.90
* **ROC-AUC:** 0.97–0.99

This shows strong discrimination between fraudulent and legitimate transactions.

### 📌 Why recall matters

Missing a fraudulent transaction (false negative) is costly.
A fraud detection system must prioritize identifying fraud **even if it produces some false alarms**.

---

## 📉 Confusion Matrix Interpretation

```
[[TN  FP]
 [FN  TP]]
```

* **TP (true positives):** correctly detected fraud
* **FP (false positives):** flagged legit transactions
* **FN (false negatives):** undetected fraud (worst)
* **TN (true negatives):** correct legit predictions

Our goal: **Minimize FN**, even at the cost of higher FP.

---

## 📈 ROC Curve and AUC

The ROC-AUC score near **0.99** indicates the model is extremely good at ranking fraudulent transactions above normal ones.

A high AUC means:

> The model is excellent at separating the two classes despite imbalance.

---

## 🧠 Insights From the Project

* Class imbalance is the main challenge.
* Accuracy is misleading — always consider precision/recall.
* XGBoost performs exceptionally well without oversampling.
* Scaling numerical features is essential for stable training.
* Fraud detection is a high-impact ML application used by real banks.

---

## 🚀 Extensions

You can expand this project by adding:

### 🔧 SMOTE oversampling

Generate synthetic fraud examples to increase recall.

### 🔍 Feature engineering

* Transaction hour
* Rolling averages
* User behavior profiles

### 🌐 Deployment

* Flask/FastAPI API
* Streamlit dashboard
* Real-time fraud alert system

---

## 🏁 Summary

In this project, we built a **high-performing fraud detection system** using:

* real-world Kaggle data
* robust preprocessing
* XGBoost for classification
* precision/recall and ROC-AUC for evaluation

```
