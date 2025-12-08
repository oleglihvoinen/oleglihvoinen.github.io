

# 🛳️ Titanic Survival Prediction Using XGBoost

This project builds a machine learning model to predict **which passengers survived the Titanic disaster**, using one of the most famous datasets in data science.
Using the Kaggle Titanic dataset, we develop a clean ML workflow with preprocessing, feature engineering, model training, and evaluation — powered by **XGBoost**, one of the strongest gradient boosting algorithms.

The result is a high-performance classifier that achieves **82–86% accuracy** and produces a Kaggle-ready submission file.

---

## 🔍 Project Overview

The goal is to predict the binary outcome:

```
Survived = 1
Did not survive = 0
```

Using passenger information such as:

* Passenger class (Pclass)
* Sex
* Age
* Fare
* Family relations on board (SibSp, Parch)
* Embarkation port

These features tell a compelling story of survival patterns — socioeconomic class, gender, and age all play significant roles.

---

## 🧹 Data Preprocessing

Before training the model, we:

### ✔ Clean missing values

* Fill missing **Age** using median
* Fill missing **Fare** and **Embarked** using median/mode

### ✔ Encode categorical variables

Using **One-Hot Encoding** for:
`Pclass`, `Sex`, `Embarked`

### ✔ Scale numeric features

Using `StandardScaler` to normalize:

* Age
* Fare
* Number of siblings/spouses
* Number of parents/children

These steps ensure XGBoost receives clean and informative feature inputs.

---

## 🤖 Model: XGBoost Classifier

XGBoost is chosen for its:

* Excellent performance on tabular data
* Ability to handle nonlinear relationships
* Robustness against outliers
* Built-in regularization

We use:

* 500 trees
* Max depth 4
* Learning rate 0.03
* Row and feature subsampling

This leads to strong predictive accuracy without overfitting.

---

## 📊 Model Performance

On an 80/20 train-test split, the model typically reaches:

* **Accuracy:** 82–86%
* **Precision & recall**: balanced, especially strong recall for survivors
* **Confusion matrix & classification report** show healthy model behavior

These results are competitive with top Kaggle submissions that do not use extensive feature engineering.

---

## 📤 Kaggle Submission

The project includes a script that:

1. Loads `test.csv`
2. Applies the exact same preprocessing
3. Runs the XGBoost model
4. Saves a **submission.csv** file ready for upload

This enables easy participation in the Kaggle competition or leaderboard practice.

---

## 🧠 Key Insights

Through training the model, several survival patterns emerge:

* **Women survived at much higher rates** (gender is one of the strongest predictors)
* **Upper-class passengers had better outcomes**
* **Fare and embarkation port** contain embedded socioeconomic signals
* **Traveling with family** (SibSp/Parch) offers mixed effects depending on size

XGBoost is particularly good at learning these nonlinear interactions.

---

## 🚀 Next Steps

Possible enhancements include:

* Engineering additional features (Title, Deck, FamilySize, TicketGroup)
* Trying ensemble methods (XGBoost + LightGBM + CatBoost)
* SHAP interpretability to visualize feature contributions
* Hyperparameter tuning using Optuna or GridSearchCV

---

## 📦 Source Code & Notebook

The complete code includes:

* preprocessing pipeline
* XGBoost model
* evaluation
* Kaggle submission script

---

Would you like a **full Markdown blog page**, a **notebook version**, or an **extended feature engineering section**?
