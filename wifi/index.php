<?php
include('jdf.php');
date_default_timezone_set('Asia/Tehran');

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "name";

$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) die("Connection failed: " . $conn->connect_error);


$name = isset($_GET['name']) ? $_GET['name'] : '';
$status = isset($_GET['status']) ? $_GET['status'] : '';
$esp32 = isset($_GET['esp32']) ? true : false;

if ($name && $status) {
    $datetime = date('Y-m-d H:i:s');

    if ($status == "ورود") {
        $time_in = $datetime;
        $time_out = NULL;
    } else { // خروج
        $time_in = NULL;
        $time_out = $datetime;
    }

    // ذخیره در دیتابیس
    $stmt = $conn->prepare("INSERT INTO esp32 (name, status, time_in, time_out) VALUES (?, ?, ?, ?)");
    $stmt->bind_param("ssss", $name, $status, $time_in, $time_out);
    $stmt->execute();
    $stmt->close();


    if ($esp32) {
        echo "Name: $name, Status: $status, Time_in: $time_in, Time_out: $time_out";
        exit;
    }
}

// نمایش جدول HTML
$sql = "SELECT * FROM esp32";
$result = $conn->query($sql);
?>

<!DOCTYPE html>
<html lang="fa" dir="rtl">
<head>
    <meta charset="UTF-8">
    <title>گزارش ورود و خروج</title>
    <script src="https://cdn.tailwindcss.com"></script>
    <link href="https://cdn.jsdelivr.net/gh/rastikerdar/shabnam-font@v5.0.1/dist/font-face.css" rel="stylesheet">
    <style>body {
            font-family: Shabnam, sans-serif;
        }</style>
</head>
<body class="bg-gray-100 min-h-screen p-6">

<div class="max-w-5xl mx-auto">
    <h1 class="text-2xl font-bold mb-6 text-gray-800">گزارش ورود و خروج</h1>

    <div class="bg-white rounded-xl shadow-lg overflow-hidden">
        <div class="overflow-x-auto">
            <table class="min-w-full text-sm text-right">
                <thead class="bg-gray-100">
                <tr>
                    <th class="px-6 py-4 font-semibold text-gray-600">نام</th>
                    <th class="px-6 py-4 font-semibold text-gray-600">تاریخ ورود</th>
                    <th class="px-6 py-4 font-semibold text-gray-600">تاریخ خروج</th>
                    <th class="px-6 py-4 font-semibold text-gray-600">وضعیت</th>
                </tr>
                </thead>
                <tbody class="divide-y">
                <?php
                if ($result->num_rows > 0) {
                    while ($row = $result->fetch_assoc()) {
                        // تبدیل میلادی به شمسی
                        $time_in = $row['time_in'] ? jdate('Y/m/d - H:i', strtotime($row['time_in'])) : '-';
                        $time_out = $row['time_out'] ? jdate('Y/m/d - H:i', strtotime($row['time_out'])) : '-';

                        echo "<tr class='hover:bg-gray-50 transition'>";
                        echo "<td class='px-6 py-4 font-medium'>" . htmlspecialchars($row['name']) . "</td>";
                        echo "<td class='px-6 py-4 text-gray-500'>$time_in</td>";
                        echo "<td class='px-6 py-4 text-gray-500'>$time_out</td>";
                        echo "<td class='px-6 py-4'><span class='px-3 py-1 rounded-full text-xs " .
                                ($row['status'] == "ورود" ? "bg-green-100 text-green-700" : "bg-red-100 text-red-700") .
                                "'>" . htmlspecialchars($row['status']) . "</span></td>";
                        echo "</tr>";
                    }
                } else {
                    echo "<tr><td colspan='4' class='px-6 py-4 text-center text-gray-500'>هیچ داده‌ای ثبت نشده است</td></tr>";
                }
                $conn->close();
                ?>
                </tbody>
            </table>
        </div>
    </div>
</div>

</body>
</html>

