namespace MoistAPI.Models
{
    public class MachineSettings
    {
        public string MachineId { get; set; }
        public bool AutomaticWatering { get; set; }
        public int AutomaticThreshold { get; set; }
        public string PartitionKey { get; set; }
    }
}
