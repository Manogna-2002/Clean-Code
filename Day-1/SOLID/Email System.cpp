using System;
using System.Collections.Generic;

// Notification channel abstraction
public interface INotificationChannel
{
    void SendNotification(string recipient, string content);
}

// Email notification channel
public class EmailNotificationChannel : INotificationChannel
{
    public void SendNotification(string recipient, string content)
    {
        // Logic to send email (HTML content, attachments, etc.)
        Console.WriteLine($"Sending email to {recipient}: {content}");
    }
}

// SMS notification channel
public class SMSNotificationChannel : INotificationChannel
{
    public void SendNotification(string recipient, string content)
    {
        // Logic to send SMS (plain text, 160 characters limit)
        Console.WriteLine($"Sending SMS to {recipient}: {content.Substring(0, Math.Min(160, content.Length))}");
    }
}

// Push notification channel
public class PushNotificationChannel : INotificationChannel
{
    public void SendNotification(string recipient, string content)
    {
        // Logic to send push notification (short text, optional actions)
        Console.WriteLine($"Sending push notification to {recipient}: {content}");
    }
}

// WhatsApp notification channel (newly added for extensibility)
public class WhatsAppNotificationChannel : INotificationChannel
{
    public void SendNotification(string recipient, string content)
    {
        // Logic to send WhatsApp message
        Console.WriteLine($"Sending WhatsApp message to {recipient}: {content}");
    }
}

// Notification service responsible for sending notifications through the provided channels
public class NotificationService
{
    private readonly List<INotificationChannel> _channels;

    public NotificationService(List<INotificationChannel> channels)
    {
        _channels = channels ?? throw new ArgumentNullException(nameof(channels));
    }

    public void SendNotification(string recipient, string content)
    {
        foreach (var channel in _channels)
        {
            channel.SendNotification(recipient, content);
        }
    }
}

class Program
{
    static void Main(string[] args)
    {
        // Configure the notification channels (can be expanded in the future)
        var emailChannel = new EmailNotificationChannel();
        var smsChannel = new SMSNotificationChannel();
        var pushChannel = new PushNotificationChannel();
        var whatsappChannel = new WhatsAppNotificationChannel(); // New WhatsApp channel

        // Creating the list of channels that the NotificationService will use
        var channels = new List<INotificationChannel> { emailChannel, smsChannel, pushChannel, whatsappChannel };

        // Create the NotificationService and send a notification
        var notificationService = new NotificationService(channels);
        notificationService.SendNotification("user@example.com", "Your appointment is confirmed!");
    }
}
