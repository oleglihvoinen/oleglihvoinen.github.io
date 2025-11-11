
# 💰 Loan Default Probability Prediction (Machine Learning Project)

## 🎯 Project Goal

The goal of this project is to **predict the probability that a borrower will pay back their loan**.  
This is a **binary classification** problem — the model estimates how likely each borrower is to repay (`1`) or default (`0`) on their loan.

Predictions are evaluated using the **Area Under the ROC Curve (AUC)**, which measures how well the model ranks high- vs. low-risk borrowers.

---

## 📊 Dataset Overview

Each record represents a borrower with personal, financial, and loan-related attributes.

| Column | Description | Type |
|---------|-------------|------|
| `id` | Unique identifier for borrower | ID |
| `annual_income` | Annual income in USD | Numeric |
| `debt_to_income_ratio` | Ratio of debt to income | Numeric |
| `credit_score` | Borrower’s credit score (300–850) | Numeric |
| `loan_amount` | Loan principal amount | Numeric |
| `interest_rate` | Loan interest rate (%) | Numeric |
| `gender` | Borrower gender | Categorical |
| `marital_status` | Marital status | Categorical |
| `education_level` | Highest education achieved | Categorical |
| `employment_status` | Employment category | Categorical |
| `loan_purpose` | Purpose of the loan | Categorical |
| `grade_subgrade` | Credit grade assigned by lender | Categorical |
| *(Train only)* `loan_paid_back` | Target variable (1 = repaid, 0 = default) | Binary |

### 🧾 Example test data
```csv
id,annual_income,debt_to_income_ratio,credit_score,loan_amount,interest_rate,gender,marital_status,education_level,employment_status,loan_purpose,grade_subgrade
593994,28781.05,0.049,626,11461.42,14.73,Female,Single,High School,Employed,Other,D5
593995,46626.39,0.093,732,15492.25,12.85,Female,Married,Master's,Employed,Other,C1
593996,54954.89,0.367,611,3796.41,13.29,Male,Single,Bachelor's,Employed,Debt consolidation,D1
593997,25644.63,0.11,671,6574.3,9.57,Female,Single,Bachelor's,Employed,Debt consolidation,C3
````

---

## 🧠 Model Objective

We train a **machine learning model** to predict the probability that a borrower repays their loan (`loan_paid_back = 1`).
The output is a **probability between 0 and 1**, not a simple yes/no label.

---

## ⚙️ Approach

### 1️⃣ Data Preprocessing

* Handle missing values
* Scale numeric features
* Encode categorical features using **One-Hot Encoding**

### 2️⃣ Model Training

* Use a **Gradient Boosting Classifier** or **XGBoost** for strong predictive performance on tabular data.
* Split the training data into 80% train / 20% validation for AUC evaluation.

### 3️⃣ Probability Prediction

The model outputs probabilities (`predict_proba`) for the positive class (loan repaid).

---

## 🧩 Example Python Pipeline

```python
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import OneHotEncoder, StandardScaler
from sklearn.compose import ColumnTransformer
from sklearn.pipeline import Pipeline
from sklearn.ensemble import GradientBoostingClassifier
from sklearn.metrics import roc_auc_score

# Load data
train = pd.read_csv("train.csv")
test = pd.read_csv("test.csv")

# Separate target
X = train.drop(["id", "loan_paid_back"], axis=1)
y = train["loan_paid_back"]

# Identify numeric and categorical columns
num_cols = X.select_dtypes(include=["float64", "int64"]).columns
cat_cols = X.select_dtypes(include=["object"]).columns

# Preprocess
preprocessor = ColumnTransformer([
    ("num", StandardScaler(), num_cols),
    ("cat", OneHotEncoder(handle_unknown="ignore"), cat_cols)
])

# Model
model = GradientBoostingClassifier(random_state=42)
pipeline = Pipeline([("preprocessor", preprocessor),
                     ("model", model)])

# Train/test split
X_train, X_val, y_train, y_val = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)
pipeline.fit(X_train, y_train)

# Validation
val_pred = pipeline.predict_proba(X_val)[:, 1]
print("Validation AUC:", roc_auc_score(y_val, val_pred))

# Predict on test
test_pred = pipeline.predict_proba(test.drop("id", axis=1))[:, 1]

# Save submission
submission = pd.DataFrame({"id": test["id"], "loan_paid_back": test_pred})
submission.to_csv("submission.csv", index=False)
print("✅ submission.csv created successfully!")
```

---

## 📈 Evaluation

Submissions are scored on the **Area Under the ROC Curve (AUC)** between the predicted probability and the actual `loan_paid_back` outcome.

| Metric      | Description                                                         |
| ----------- | ------------------------------------------------------------------- |
| **AUC-ROC** | Measures how well the model ranks borrowers by repayment likelihood |
| **Range**   | 0.5 (random) → 1.0 (perfect)                                        |
| **Goal**    | Maximize AUC by improving feature selection & model tuning          |

---

## 📤 Submission Format

The final submission file must contain two columns:
`id` and the **predicted probability** of repayment.

Example:

```csv
id,loan_paid_back
593994,0.5012
593995,0.2087
593996,0.8124
```

---

## 🧮 Model Improvements

🔧 **Feature Engineering**

* Create `loan_to_income_ratio = loan_amount / annual_income`
* Encode risk from `grade_subgrade`
* Aggregate historical defaults per borrower

🧠 **Advanced Models**

* [XGBoost](https://xgboost.readthedocs.io/)
* [LightGBM](https://lightgbm.readthedocs.io/)
* [CatBoost](https://catboost.ai/)

📊 **Explainability**

* Use [SHAP](https://shap.readthedocs.io/en/latest/) values to interpret which features drive predictions.

---

## 🧾 Results

A well-tuned gradient boosting model typically achieves **AUC > 0.80**, indicating strong discriminatory power between likely defaulters and reliable borrowers.

---

## 💼 Key Takeaways

* Predicting loan repayment probability helps financial institutions assess **credit risk**.
* AUC is an ideal metric because it focuses on **ranking quality**, not fixed thresholds.
* Clean data, engineered features, and model interpretability are the keys to real-world deployment.

---

## 🧩 Tools Used

| Tool                           | Purpose                          |
| ------------------------------ | -------------------------------- |
| **Python 3.10+**               | Core language                    |
| **pandas / scikit-learn**      | Data handling & modeling         |
| **GradientBoosting / XGBoost** | Machine learning algorithms      |
| **ROC-AUC**                    | Model evaluation                 |
| **Matplotlib / SHAP**          | Visualization & interpretability |

---

## 🧠 Author

**Oleg Lihvoinen**
Data & AI Engineer | LLM & MDM Enthusiast
📍 Finland
🔗 [GitHub: oleglihvoinen](https://github.com/oleglihvoinen)

---

> 💡 *"In credit scoring, probability is power — every decimal point improves risk understanding and financial safety."*

```

---
