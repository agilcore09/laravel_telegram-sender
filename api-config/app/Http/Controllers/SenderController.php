<?php

namespace App\Http\Controllers;

use App\Notifications\SendNotification;
use Illuminate\Http\Request;

use Illuminate\Support\Facades\Notification;

class SenderController extends Controller
{
    public function sender()
    {
        $user = [-4089501598];
        Notification::send($user, new SendNotification());

        $data = [
            'message' => 'Success Mengirim Alarm',
        ];
        return response()->json($data);
    }
}
