using System;

namespace MoistAPI.Models
{
    public class MoistureReading
    {
        public string MachineId { get; set; }
        public int MoistureLevel { get; set; }
        public DateTime Timestamp { get; set; }
    }
}
