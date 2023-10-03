using System.ComponentModel.DataAnnotations;

public class Discipline
{
    public int Id { get; set; }

    [Required, StringLength(70, MinimumLength = 3)]
    [RegularExpression(@"[а-яА-Яa-zA-Z-\s()""]+$", ErrorMessage = "Invalid name")]
    public string Name { get; set; }

    [Required, Range(1, int.MaxValue)]
    public int Hours { get; set; }

    [Required, Range(0, int.MaxValue)]
    public int LectureHours { get; set; }

    [Required, Range(0, int.MaxValue)]
    public int LabHours { get; set; }

    [Required]
    public string CertificationType { get; set; }
}