
typedef struct s_message {
  float m_left; ///< Moment in X (Mx)
  float m_right; ///< Moment in Y (My)
  int16_t mode; ///< Force in Z (Fz)
}__attribute__((packed)) s_message_t;
