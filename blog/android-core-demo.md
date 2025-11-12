

# 📱 Android Development — Core Elements & Lists, Layouts, and Images 

*by **Oleg Lihvoinen***
*GitHub Pages: [oleglihvoinen.github.io](https://oleglihvoinen.github.io)*
*Video demo: [link to video placeholder — replace with your YouTube link]*

---

## 🎯 Overview

In this part of my Android learning series, I built a small app to practice **core Android components** and **UI list layouts**.
This project covers:

* **Activities**, **Intents**, **IntentServices**, and **BroadcastReceivers**
* **ListView** and **custom layouts**
* **Images with ImageView**
* **Multiple screens (views)**
* **Buttons, Text Fields, and Toggle Buttons**
* Custom **style and theme** with my name and a personalized touch

---

## 📂 Project: “Oleg’s Android Core Demo”

### 🧱 Structure

```
app/
 ├── java/com/example/coreelements/
 │    ├── MainActivity.java
 │    ├── DetailActivity.java
 │    ├── MyIntentService.java
 │    ├── MyBroadcastReceiver.java
 │    └── AnimalAdapter.java
 ├── res/
 │    ├── layout/
 │    │    ├── activity_main.xml
 │    │    ├── activity_detail.xml
 │    │    └── list_item.xml
 │    ├── drawable/ (images)
 │    ├── values/
 │    │    ├── colors.xml
 │    │    ├── strings.xml
 │    │    └── styles.xml
 └── AndroidManifest.xml
```

---

## 💡 Core Features

### 1. **MainActivity**

Displays a **ListView** of animals with names and images.
When an item is clicked, it starts a **DetailActivity** using an **Intent** and passes the selected animal name as an extra.

```java
// MainActivity.java
package com.example.coreelements;

import android.content.Intent;
import android.os.Bundle;
import android.widget.ListView;
import androidx.appcompat.app.AppCompatActivity;
import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        setTitle("Oleg Lihvoinen – Core Elements Demo");

        ArrayList<Animal> animals = new ArrayList<>();
        animals.add(new Animal("Cat", R.drawable.cat));
        animals.add(new Animal("Dog", R.drawable.dog));
        animals.add(new Animal("Rabbit", R.drawable.rabbit));

        AnimalAdapter adapter = new AnimalAdapter(this, animals);
        ListView listView = findViewById(R.id.listView);
        listView.setAdapter(adapter);

        listView.setOnItemClickListener((adapterView, view, i, l) -> {
            Animal selected = animals.get(i);
            Intent intent = new Intent(MainActivity.this, DetailActivity.class);
            intent.putExtra("animal_name", selected.getName());
            startActivity(intent);
        });
    }
}
```

---

### 2. **AnimalAdapter** (Custom Layout for ListView)

```java
// AnimalAdapter.java
package com.example.coreelements;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import java.util.List;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import android.widget.ArrayAdapter;

public class AnimalAdapter extends ArrayAdapter<Animal> {

    public AnimalAdapter(Context context, List<Animal> animals) {
        super(context, 0, animals);
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {
        if (convertView == null) {
            convertView = LayoutInflater.from(getContext()).inflate(R.layout.list_item, parent, false);
        }
        Animal animal = getItem(position);
        TextView name = convertView.findViewById(R.id.textView);
        ImageView image = convertView.findViewById(R.id.imageView);
        name.setText(animal.getName());
        image.setImageResource(animal.getImageResId());
        return convertView;
    }
}
```

---

### 3. **DetailActivity**

Shows more info and starts a background task (**IntentService**) when opened.

```java
// DetailActivity.java
package com.example.coreelements;

import android.content.Intent;
import android.os.Bundle;
import android.widget.TextView;
import androidx.appcompat.app.AppCompatActivity;

public class DetailActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_detail);

        String animalName = getIntent().getStringExtra("animal_name");
        TextView text = findViewById(R.id.textViewDetail);
        text.setText("Selected Animal: " + animalName);

        // Start IntentService
        Intent serviceIntent = new Intent(this, MyIntentService.class);
        serviceIntent.putExtra("animal_name", animalName);
        startService(serviceIntent);
    }
}
```

---

### 4. **IntentService and BroadcastReceiver**

```java
// MyIntentService.java
package com.example.coreelements;

import android.app.IntentService;
import android.content.Intent;
import android.content.Context;

public class MyIntentService extends IntentService {

    public MyIntentService() {
        super("MyIntentService");
    }

    @Override
    protected void onHandleIntent(Intent intent) {
        String name = intent.getStringExtra("animal_name");
        try {
            Thread.sleep(2000); // simulate work
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        Intent broadcastIntent = new Intent("com.example.ACTION_DONE");
        broadcastIntent.putExtra("message", name + " info processed!");
        sendBroadcast(broadcastIntent);
    }
}
```

```java
// MyBroadcastReceiver.java
package com.example.coreelements;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.widget.Toast;

public class MyBroadcastReceiver extends BroadcastReceiver {
    @Override
    public void onReceive(Context context, Intent intent) {
        String msg = intent.getStringExtra("message");
        Toast.makeText(context, msg, Toast.LENGTH_LONG).show();
    }
}
```

Register the receiver in `AndroidManifest.xml`:

```xml
<receiver android:name=".MyBroadcastReceiver">
    <intent-filter>
        <action android:name="com.example.ACTION_DONE" />
    </intent-filter>
</receiver>
```

---

### 5. **Custom Layouts**

**activity_main.xml**

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="vertical"
    android:background="@color/light_gray"
    android:padding="16dp"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <ListView
        android:id="@+id/listView"
        android:layout_width="match_parent"
        android:layout_height="wrap_content" />
</LinearLayout>
```

**list_item.xml**

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="horizontal"
    android:padding="8dp"
    android:layout_width="match_parent"
    android:layout_height="wrap_content">

    <ImageView
        android:id="@+id/imageView"
        android:layout_width="60dp"
        android:layout_height="60dp"
        android:layout_marginEnd="10dp" />

    <TextView
        android:id="@+id/textView"
        android:textSize="20sp"
        android:textColor="@color/black"
        android:layout_gravity="center_vertical"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content" />
</LinearLayout>
```

**activity_detail.xml**

```xml
<LinearLayout xmlns:android="http://schemas.android.com/apk/res/android"
    android:orientation="vertical"
    android:gravity="center"
    android:padding="16dp"
    android:layout_width="match_parent"
    android:layout_height="match_parent">

    <TextView
        android:id="@+id/textViewDetail"
        android:text="Animal Detail"
        android:textSize="22sp"
        android:layout_width="wrap_content"
        android:layout_height="wrap_content" />
</LinearLayout>
```

---

## ▶️ How to Run the Project

1. Clone or download the repository

   ```bash
   git clone https://github.com/oleglihvoinen/android-core-demo.git
   ```

2. Open the project in **Android Studio**.

3. Let Gradle sync and run the project on:

   * **Android Emulator**, or
   * **Physical device** (with USB debugging enabled).

4. Tap an animal → go to detail screen → after 2 seconds, a **Toast** message appears via **BroadcastReceiver**.

---

## 🧠 Learning Diary

**What I learned:**

* The relationship between **Activity**, **Intent**, **IntentService**, and **BroadcastReceiver**.
* How to use **ListView** with custom layouts.
* How to pass data between screens.
* How to add background tasks and display results asynchronously.
* How XML layout design affects UI structure.
* How Android handles **lifecycle and broadcasts**.
* How small UI details and colors make the app “mine.”

**Next goal:**
Move from `ListView` to `RecyclerView` and add data persistence with Room or SharedPreferences.

---

## 🎥 Video Demo

[👉 Watch the project running here](#) *(replace with your YouTube or Loom link)*


